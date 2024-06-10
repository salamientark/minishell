/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:25:32 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/10 17:41:17 by ple-guya         ###   ########.fr       */
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

// void	redirect_for_next_cmd(t_chill *shell)
// {
// 	if (shell->nb_cmd == 1)
// 		return ;
// 	if (!is_last_cmd(shell))
// 	{
// 		close(shell->pipefd[WRITE_END]);
// 		dup2(shell->pipefd[READ_END], STDIN_FILENO);
// 		close(shell->pipefd[READ_END]);
// 	}
// 	else if (is_last_cmd(shell))
// 	{
// 		close (shell->pipefd[WRITE_END]);
// 		close(shell->pipefd[READ_END]);
// 	}
// }

void	redirect(t_chill *shell)
{
	if (shell->nb_cmd == 1)
		case_no_pipe(shell);
	else if (shell->index_cmd == 0)
	{
		close(shell->pipefd[READ_END]);
		dup2(shell->fd_in, STDIN_FILENO);
		close(shell->fd_in);
		close(shell->fd_out);
		dup2(shell->pipefd[WRITE_END], STDOUT_FILENO);
		close(shell->pipefd[WRITE_END]);
	}
	else if (is_last_cmd(shell))
	{
		dup2(shell->pipefd[READ_END], STDIN_FILENO);
		close(shell->pipefd[READ_END]);
		dup2(shell->fd_out, STDOUT_FILENO);
		close(shell->fd_out);
	}
	else if (!is_last_cmd(shell))
	{
		dup2(shell->old_fd, STDIN_FILENO);
		close(shell->old_fd);
		dup2(shell->pipefd[WRITE_END], STDOUT_FILENO);
		close(shell->pipefd[WRITE_END]);
		close (shell->fd_in);
		close (shell->fd_out);
	}
}
