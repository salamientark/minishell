/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:25:32 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/10 15:25:39 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	case_no_pipe(t_chill *shell)
{
	if(shell->infile)
	{
		dup2(shell->fd_in, STDIN_FILENO);
		close (shell->fd_in);
	}
	if (shell->outfile)
	{
		dup2(shell->fd_out, STDOUT_FILENO);
		close (shell->fd_in);
	}
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
		if (shell->infile)
		{
			dup2(shell->fd_in, STDIN_FILENO);
			close(shell->fd_in);
		}
		if (shell->outfile)
		{
			dup2(shell->fd_out, STDOUT_FILENO);
			close(shell->fd_out);
		}
		if (!shell->outfile)
			dup2(shell->pipefd[WRITE_END], STDOUT_FILENO);
		close(shell->pipefd[WRITE_END]);
		close(shell->pipefd[READ_END]);
	}
	else if (!is_last_cmd(shell))
	{
		close(shell->pipefd[READ_END]);
		if (shell->outfile)
		{
			dup2(shell->fd_out, STDOUT_FILENO);
			close(shell->fd_out);
		}
		if(!shell->infile)
		{
			dup2(shell->old_fd, STDIN_FILENO);
			close(shell->old_fd);
		}
		if (!shell->outfile)
			dup2(shell->pipefd[WRITE_END], STDOUT_FILENO);
		close(shell->pipefd[WRITE_END]);
	}
	else if (is_last_cmd(shell))
	{
		if(shell->infile)
		{
			dup2(shell->fd_in, STDIN_FILENO);
			close(shell->fd_in);
		}
		if(!shell->infile)
			dup2(shell->pipefd[READ_END], STDIN_FILENO);
		if(shell->outfile)
		{
			dup2(shell->fd_out, STDOUT_FILENO);
			close(shell->fd_out);
		}
		close(shell->pipefd[READ_END]);
		close(shell->pipefd[WRITE_END]);
	}
}
