/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:11:13 by madlab            #+#    #+#             */
/*   Updated: 2024/06/03 20:06:06 by dbaladro         ###   ########.fr       */
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
	memset(str + pos, 0, len - pos);
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
	limiter = (char *)malloc(limiter_len + 2);
	if (!limiter)
		return (print_error("malloc", strerror(errno)), NULL);
	limiter[limiter_len] = '\n';
	limiter[limiter_len + 1] = '\0';
	while (limiter_len-- > 0)
		limiter[limiter_len] = cmd[index + limiter_len];
	if (*expand_flag == 0)
		str_remove_quote(limiter);
	return (limiter);
}

/* Perform variable expansion on heredoc input
 * */
static char	*expand_heredoc_input(char *input, char **env)
{
	t_expand	**expand_tab;
	char		*result;
	int			index;

	index = 0;
	while (input[index] && !is_expand(input + index))
		index++;
	if (!input[index])
		return (input);
	expand_tab = (t_expand **)malloc(sizeof(t_expand *) * 2);
	if (!expand_tab)
		return (print_error("malloc", strerror(errno)), free(input), NULL);
	expand_tab[1] = NULL;
	expand_tab[0] = make_expand_elem(input);
	if (!expand_tab[0])
		return (free(expand_tab), free(input), NULL);
	memset(expand_tab[0]->quote, 0, sizeof(int) * expand_tab[0]->size);
	expand_tab[1] = NULL;
	if (perform_variable_expansion(expand_tab, env) != 0)
		return (free_expand_tab(&expand_tab), free(input), NULL);
	result = expand_tab[0]->word;
	expand_tab[0]->word = NULL;
	free_expand_tab(&expand_tab);
	return (result);
}

/* Write standard input to fd
 * */
static int	write_here_doc(int fd, char *limiter, int expand_flag, char **env)
{
	int		index;
	int		limiter_len;
	char	*input;

	limiter_len = 0;
	while (limiter[limiter_len] && limiter[limiter_len] != '\n')
		limiter_len++;
	index = 0;
	write(1, HERE_DOC_PROMPT, 2);
	input = get_next_line(0);
	while (input && ft_strncmp(input, limiter, limiter_len + 1) != 0)
	{
		if (expand_flag == 1)
			input = expand_heredoc_input(input, env);
		if (!input)
			return (free(limiter), 1);
		index++;
		write(fd, input, ft_strlen(input));
		free(input);
		write(1, HERE_DOC_PROMPT, 2);
		input = get_next_line(0);
	}
	if (!input)
		return (free(limiter), print_here_doc_warning(index, limiter), 0);
	return (free(input), free(limiter), 0);
}

/* File redirection 
 * */
int	here_doc(const char *cmd, int ref, int *here_doc_count, char **env)
{
	char	*limiter;
	char	heredoc_filename[11];
	int		expand_flag;
	int		fd;

	fd = open(here_doc_name(heredoc_filename, *here_doc_count),
			O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
	if (fd == -1)
		return (print_error("open", strerror(errno)), 1);
	expand_flag = 1;
	limiter = get_here_doc_limiter(cmd, ref, &expand_flag);
	if (!limiter)
		return (1);
	printf("limiter : %s\n", limiter);
	if (write_here_doc(fd, limiter, expand_flag, env) != 0)
		return (1);
	close(fd);
	*here_doc_count += 1;
	return (0);
}
