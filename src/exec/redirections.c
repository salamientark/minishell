/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:25:32 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/08 21:58:45 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	case_no_pipe(t_chill *shell)
{
	if(shell->infile)
		dup2(shell->fd_in, STDIN_FILENO);
	if (shell->outfile)
		dup2(shell->fd_out, STDOUT_FILENO);
}

void	redirect_for_next_cmd(t_chill *shell)
{
	if (shell->nb_cmd == 1)
		return ;
	if (!is_last_cmd(shell))
	{
		close(shell->pipefd[WRITE_END]);
		dup2(shell->pipefd[READ_END], STDIN_FILENO);
		close(shell->pipefd[READ_END]);
	}
	else if (is_last_cmd(shell))
	{
		close (shell->pipefd[WRITE_END]);
		close(shell->pipefd[READ_END]);
	}
}

void	redirect(t_chill *shell, char **redirection)
{
	get_file(shell, redirection);
	if (shell->nb_cmd == 1)
		case_no_pipe(shell);
	else if (shell->nb_cmd == shell->index_cmd + 1)
	{
		if(shell->infile)
			dup2(shell->fd_in, STDIN_FILENO);
		if (shell->outfile)
			dup2(shell->fd_out, STDOUT_FILENO);
		if(!shell->infile)
			dup2(shell->pipefd[WRITE_END], STDIN_FILENO);
	}
	else if (shell->nb_cmd != shell->index_cmd + 1)
	{
		if(shell->infile)
			dup2(shell->fd_in, STDIN_FILENO);
		if (!shell->outfile)
		{
			close(shell->pipefd[READ_END]);
			dup2(shell->pipefd[WRITE_END], STDOUT_FILENO);
			close(shell->pipefd[READ_END]);
		}
		else
			dup2(shell->fd_out, STDOUT_FILENO);
	}
}
