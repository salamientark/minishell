/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:25:32 by ple-guya          #+#    #+#             */
/*   Updated: 2024/07/17 20:42:10 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	case_no_pipe(t_chill *shell)
{
	dup2(shell->fd_in, STDIN_FILENO);
	close (shell->fd_in);
	dup2(shell->fd_out, STDOUT_FILENO);
	close(shell->fd_out);
}

static void	first_child(t_chill *shell)
{
	if (shell->old_fd != -1)
		close (shell->old_fd);
	close(shell->pipefd[READ_END]);
	dup2(shell->fd_in, STDIN_FILENO);
	dup2(shell->pipefd[WRITE_END], STDOUT_FILENO);
	close(shell->pipefd[WRITE_END]);
	close(shell->fd_in);
	if (shell->outfile)
		dup2(shell->fd_out, STDOUT_FILENO);
	close(shell->fd_out);
}

static void	intermediate_child(t_chill *shell)
{
	dup2(shell->old_fd, STDIN_FILENO);
	close (shell->old_fd);
	dup2(shell->pipefd[WRITE_END], STDOUT_FILENO);
	close(shell->pipefd[WRITE_END]);
	close(shell->pipefd[READ_END]);
	if (shell->infile)
		dup2(shell->fd_in, STDIN_FILENO);
	close(shell->fd_in);
	if (shell->outfile)
		dup2(shell->fd_out, STDOUT_FILENO);
	close(shell->fd_out);
	// dprintf(2, "intermediate\n");
	// dprintf(2, "fd_in %d || fd_out %d\n", shell->fd_in, shell->fd_out);
	// dprintf(2, "old_fd %d || shell->pipefd[WRITE_END] %d\n", shell->old_fd, shell->pipefd[WRITE_END]);
	// dprintf(2, "pipe[READ] %d\n", shell->pipefd[READ_END]);
}

static void	last_child(t_chill *shell)
{
	if (shell->infile)
		dup2(shell->fd_in, STDIN_FILENO);
	else
		dup2(shell->old_fd, STDIN_FILENO);
	dup2(shell->fd_out, STDOUT_FILENO);
	close(shell->old_fd);
	close(shell->pipefd[WRITE_END]);
	close (shell->pipefd[READ_END]);
	close(shell->fd_in);
	close(shell->fd_out);
	// dprintf(2, "last\n");
	// dprintf(2, "fd_in %d || fd_out %d\n", shell->fd_in, shell->fd_out);
	// dprintf(2, "old_fd %d || shell->pipefd[WRITE_END] %d\n", shell->old_fd, shell->pipefd[WRITE_END]);
	// dprintf(2, "pipe[READ] %d\n", shell->pipefd[READ_END]);
}

void	redirect(t_chill *shell)
{
	if (shell->nb_cmd == 1)
		case_no_pipe(shell);
	else if (shell->index_cmd == 0)
		first_child(shell);
	else if (!is_last_cmd(shell))
		intermediate_child(shell);
	else if (is_last_cmd(shell))
		last_child(shell);
}
