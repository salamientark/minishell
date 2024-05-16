/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 22:11:13 by madlab            #+#    #+#             */
/*   Updated: 2024/05/16 17:49:20 by dbaladro         ###   ########.fr       */
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

static void	print_here_doc_warning(int line, char *limiter)
{
	write(1, HERE_DOC_WARNING_MSG_1, 43);
	ft_putnbr_fd(line, 1);
	write(1, HERE_DOC_WARNING_MSG_2, 35);
	ft_putstr_fd(limiter, 1);
	write(1, HERE_DOC_WARNING_MSG_3, 3);
}

static char	*get_here_doc_limiter(const char *cmd, int ref)
{
	int		index;
	int		limiter_len;
	char	*limiter;

	index = ref + 2;
	limiter_len = 0;
	while (cmd[index] && (cmd[index] == SPACE || cmd[index] == TAB))
		index++;
	while (cmd[index + limiter_len] && !is_metachar(cmd[index + limiter_len]))
		limiter_len++;
	limiter = (char *)malloc(limiter_len + 1);
	if (!limiter)
		return (print_error("malloc", strerror(errno)), NULL);
	limiter[limiter_len] = '\n';
	while (limiter_len-- > 0)
		limiter[limiter_len] = cmd[index + limiter_len];
	return (limiter);
}

static int	write_here_doc(char *limiter, int limiter_len, int pipe_fd[2])
{
	int		index;
	char	*here_doc_input;

	close(pipe_fd[0]);
	index = 0;
	write(1, HERE_DOC_PROMPT, 2);
	here_doc_input = get_next_line(0);
	while (here_doc_input && ft_strncmp(here_doc_input, limiter,
			limiter_len + 1) != 0)
	{
		index++;
		write(pipe_fd[1], here_doc_input, ft_strlen(here_doc_input));
		free(here_doc_input);
		write(1, HERE_DOC_PROMPT, 2);
		here_doc_input = get_next_line(0);
	}
	if (!here_doc_input)
		print_here_doc_warning(index, limiter);
	else
		free(here_doc_input);
	close(pipe_fd[1]);
	exit(EXIT_SUCCESS);
}

static int	get_limiter_len(char *limiter)
{
	int	limiter_len;

	limiter_len = 0;
	while (limiter[limiter_len] && limiter[limiter_len] != '\n')
		limiter_len++;
	return (limiter_len);
}

// PIPE REDIRECTION USING FORK
int	here_doc(const char *cmd, int ref, int stdin_fd)
{
	char	*limiter;
	int		limiter_len;
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) != 0)
		return (print_error("pipe", strerror(errno)), 1);
	if (dup2(stdin_fd, STDIN_FILENO) != 0)
		return (print_error("dup2", strerror(errno)), 1);
	limiter = get_here_doc_limiter(cmd, ref);
	if (!limiter)
		return (1);
	limiter_len = get_limiter_len(limiter);
	pid = fork();
	if (pid == -1)
		return (print_error("fork", strerror(errno)), free(limiter), 1);
	if (pid == 0)
		exit(write_here_doc(limiter, limiter_len, pipe_fd));
	waitpid(pid, NULL, 0);
	close(pipe_fd[1]);
	if (dup2(pipe_fd[0], STDIN_FILENO) != 0)
		return (print_error("dup2", strerror(errno)), close(pipe_fd[0]),
			free(limiter), 1);
	return (close(pipe_fd[0]), free(limiter), 0);
}
// ====

// FILE HERE_DOC
//
// static int	write_here_doc(char *limiter, int limiter_len)
// {
// 	int		index;
// 	int		fd;
// 	char	*here_doc_input;
// 
// 	index = 0;
// 	fd = open(HERE_DOC_FILE, O_WRONLY | O_CREAT | O_EXCL | O_TRUNC, 0600);
// 	if (fd == -1)
// 		return (print_error("open", strerror(errno)), 1);
// 	write(1, HERE_DOC_PROMPT, 2);
// 	here_doc_input = get_next_line(0);
// 	while (here_doc_input && ft_strncmp(here_doc_input, limiter,
// 			limiter_len + 1) != 0)
// 	{
// 		index++;
// 		write(fd, here_doc_input, ft_strlen(here_doc_input));
// 		free(here_doc_input);
// 		write(1, HERE_DOC_PROMPT, 2);
// 		here_doc_input = get_next_line(0);
// 	}
// 	if (!here_doc_input)
// 		print_here_doc_warning(index, limiter);
// 	else
// 		free(here_doc_input);
// 	close(fd);
// 	return (0);
// }
// 
// // PIPE REDIRECTION
// int	here_doc(const char *cmd, int ref)
// {
// 	char	*limiter;
// 	int		limiter_len;
// 	int		fd;
// 
// 	limiter = get_here_doc_limiter(cmd, ref);
// 	if (!limiter)
// 		return (1);
// 	limiter_len = 0;
// 	while (limiter[limiter_len] != '\n')
// 		limiter_len++;
// 	write(1, "limiter : \'", 11);
// 	write(1, limiter, limiter_len);
// 	write(1, "\"\n", 2);
// 	if (write_here_doc(limiter, limiter_len) == 1)
// 		return (free(limiter), 1);
// 	fd = open(HERE_DOC_FILE, O_RDONLY);
// 	if (fd == -1)
// 		return (free(limiter), print_error("open", strerror(errno)), 1);
// 	if (dup2(fd, 0) != 0)
// 		return (free(limiter), close(fd), unlink(HERE_DOC_FILE),
// 			print_error("dup2", strerror(errno)), 1);
// 	unlink(HERE_DOC_FILE);
// 	close(fd);
// 	return (free(limiter), 0);
// }
