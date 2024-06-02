/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:11:13 by madlab            #+#    #+#             */
/*   Updated: 2024/06/02 23:03:17 by madlab           ###   ########.fr       */
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

/* Make here_doc filename based on couunt (+ maybe shlvl in the future)
 * */
static char	*here_doc_name(char buff_name[11], int here_doc_count)
{
	buff_name[0] = '/';
	buff_name[1] = 't';
	buff_name[2] = 'm';
	buff_name[3] = 'p';
	buff_name[4] = '/';
	buff_name[5] = '.';
	buff_name[6] = '0';
	buff_name[7] = '0';
	buff_name[8] = '0';
	buff_name[9] = (here_doc_count / 10) + '0';
	buff_name[10] = (here_doc_count % 10) + '0';
	buff_name[11] = '\0';
	return (buff_name);
}

/* Remove quote on here_doc limiter when found
 * */
static void	str_remove_quote(char *str)
{
	char	quote;
	int		pos;
	int		diff;
	size_t	len;

	pos = 0;
	diff = 0;
	len = ft_strlen(str);
	while (str[pos + diff])
	{
		if (str[pos + diff] == SINGLE_QUOTE || str[pos + diff] == DOUBLE_QUOTE)
		{
			quote = str[pos + diff];
			ft_memmove(str + pos + diff, str + pos + diff + 1, len - (pos + diff));
			pos += quoted_strlen(str, pos + diff - 1, quote) - 2;
			ft_memmove(str + pos + diff, str + pos + diff + 1, len - pos - diff);
		}
		else
		{
			str[pos] = str[pos + diff];
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
			*expand_flag = 1;
		limiter_len++;
	}
	limiter = (char *)malloc(limiter_len + 2);
	if (!limiter)
		return (print_error("malloc", strerror(errno)), NULL);
	limiter[limiter_len] = '\n';
	limiter[limiter_len + 1] = '\0';
	while (limiter_len-- > 0)
		limiter[limiter_len] = cmd[index + limiter_len];
	if (*expand_flag == 1)
		str_remove_quote(limiter);
	return (limiter);
}

/* Write standard input to fd
 * */
static void	write_here_doc(int fd, char *limiter, int limiter_len)
{
	int		index;
	char	*input;

	index = 0;
	write(1, HERE_DOC_PROMPT, 2);
	input = get_next_line(0);
	while (input && ft_strncmp(input, limiter, limiter_len + 1) != 0)
	{
		index++;
		write(fd, input, ft_strlen(input));
		free(input);
		write(1, HERE_DOC_PROMPT, 2);
		input = get_next_line(0);
	}
	if (!input)
		print_here_doc_warning(index, limiter);
	else
		free(input);
	free(limiter);
}

/* File redirection 
 * */
int	here_doc(const char *cmd, int ref, int *here_doc_count)
{
	char	*limiter;
	char	heredoc_filename[11];
	int		limiter_len;
	int		expand_flag;
	int		fd;

	fd = open(here_doc_name(heredoc_filename, *here_doc_count),
		O_WRONLY|O_CREAT|O_EXCL|O_TRUNC, 0600);
	if (fd == -1)
		return (print_error("open", strerror(errno)), 1);
	expand_flag = 0;
	limiter = get_here_doc_limiter(cmd, ref, &expand_flag);
	if (!limiter)
		return (1);
	printf("limiter : %s\n", limiter);
	limiter_len = 0;
	while (limiter[limiter_len] && limiter[limiter_len] != 0)
		limiter_len++;
	write_here_doc(fd, limiter, limiter_len);
	close(fd);
	*here_doc_count += 1;
	return (0);
}
