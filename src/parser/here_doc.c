/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:11:13 by madlab            #+#    #+#             */
/*   Updated: 2024/06/11 06:44:29 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Actually here_doc are openede as a pipe.
 * the father dup the original fd then it pipe & fork
 * The son process then dup2 the original stdin to STDIN_FILENO
 * and write to here_doc
 *
 * ==> It means that if more than one here_doc are opened the dup2
 * of the original stdin to STDIN_FILENO 'reset' what was previously wrote
 * */

#include "parser.h"
#include "expander.h"
#include "minishell.h"

extern int	g_exit_status;

/* Remove quote on here_doc limiter when found
 * */
static void	str_remove_quote(char *str)
{
	char	quote;
	int		pos;
	int		dif;
	size_t	len;

	pos = 0;
	dif = 0;
	len = ft_strlen(str);
	while (str[pos + dif])
	{
		if (str[pos + dif] == SINGLE_QUOTE || str[pos + dif] == DOUBLE_QUOTE)
		{
			quote = str[pos + dif];
			ft_memmove(str + pos + dif, str + pos + dif + 1, len - pos - dif);
			pos += quoted_strlen(str, pos + dif - 1, quote) - 2;
			ft_memmove(str + pos + dif, str + pos + dif + 1, len - pos - dif);
		}
		else
		{
			str[pos] = str[pos + dif];
			pos++;
		}
	}
	ft_memset(str + pos, 0, len - pos);
}

/* Get limiter + remove quote when found
 * */
static char	*get_here_doc_limiter(const char *cmd, int ref, int *expand_flag)
{
	int		index;
	int		limiter_len;
	char	*limiter;

	index = ref + 2;
	limiter_len = 0;
	while (cmd[index] && (cmd[index] == SPACE || cmd[index] == TAB))
		index++;
	while (cmd[index + limiter_len] && !is_metachar(cmd[index + limiter_len]))
	{
		if (cmd[index + limiter_len] == SINGLE_QUOTE
			|| cmd[index + limiter_len] == DOUBLE_QUOTE)
			*expand_flag = 0;
		limiter_len++;
	}
	limiter = (char *)malloc(limiter_len + 1);
	if (!limiter)
		return (print_error("malloc", strerror(errno)), NULL);
	limiter[limiter_len] = '\0';
	while (limiter_len-- > 0)
		limiter[limiter_len] = cmd[index + limiter_len];
	if (*expand_flag == 0)
		str_remove_quote(limiter);
	return (limiter);
}

/* Write standard input to fd
 * */
static int	write_here_doc(int fd, char *limiter, int expand_flag, char **env)
{
	int		index;
	char	*input;

	index = 0;
	while (g_exit_status != 130)
	{
		input = readline("> ");
		if (!input && g_exit_status != 130)
			return (print_here_doc_warning(index, limiter), 0);
		if (!input)
			break ;
		if (ft_strcmp(limiter, input) == 0)
			break ;
		if (expand_flag == 1)
			input = expand_heredoc(input, env);
		if (!input)
			break ;
		index++;
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	return (g_exit_status);
}

/* set the g_sig_status to 0 and open heredoc_file
 * */
int	init_here_doc(int here_doc_count)
{
	char	heredoc_name[11];
	int		fd;

	g_exit_status = 0;
	here_doc_name(heredoc_name, here_doc_count);
	fd = open(here_doc_name(heredoc_name, here_doc_count),
			O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (fd == -1)
		return (print_error("open", strerror(errno)), 1);
	signal(SIGINT, heredoc_sig_handler);
	return (fd);
}

/* Save original STDIN_FILENO befor redirecting it the the heredoc_file stream
 * */
int	here_doc(const char *cmd, int ref, int *here_doc_count, char **env)
{
	int		fd;
	int		stdin_cp;
	int		expand_flag;
	int		here_doc_return;
	char	*limiter;

	fd = init_here_doc(*here_doc_count);
	if (fd <= -1)
		return (1);
	stdin_cp = dup(STDIN_FILENO);
	if (!stdin_cp)
		return (print_error("dup", strerror(errno)), close(fd), 1);
	expand_flag = 1;
	limiter = get_here_doc_limiter(cmd, ref, &expand_flag);
	if (!limiter)
		return (close(fd), 1);
	here_doc_return = write_here_doc(fd, limiter, expand_flag, env);
	free(limiter);
	close(fd);
	close(STDIN_FILENO);
	dup2(stdin_cp, STDIN_FILENO);
	close(stdin_cp);
	signal(SIGINT, signal_handler);
	return (here_doc_return);
}
