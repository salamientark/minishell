/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:17:30 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/10 21:42:48 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int cmd_count(t_simple_cmd **cmd)
{
	int i;
	i = 0;
	
	while (cmd[i])
		i++;
	return (i); 
}

static	void	init_pipe(t_chill *shell)
{
	if (shell->nb_cmd == 1)
		return ;
	else if (shell->index_cmd == 0)
	{
		if (pipe(shell->pipefd) < 0)
		{
			perror("pipe");
			exit(1);
		}
	}
	else if (shell->index_cmd != shell->nb_cmd - 1)
	{
		shell->old_fd = dup(shell->pipefd[READ_END]);
		if (pipe(shell->pipefd) < 0)
		{
			perror("pipe");
			exit(1);
		}
	}
}

int	is_last_cmd(t_chill *shell)
{
	if (shell->nb_cmd -1 == shell->index_cmd)
		return(1);
	return(0);
}

static void wait_command(t_chill *shell)
{
	while(shell->index_cmd--)
	{
		wait(&shell->exit_status);
		shell->error_code = WEXITSTATUS(shell->exit_status);
	}
}

static void exec(t_chill *shell, char **cmd)
{
	char *path;

	path = get_valid_path(*cmd, shell->env);
	if (!path)
		exit(1);
	if (shell->fd_in == -1)
		close (shell->pipefd[1]);
	execve(path, cmd, shell->env);
	free(path);
}

static void	close_fd(t_chill *shell)
{
	if (shell->nb_cmd == 1)
	{
		close (shell->fd_in);
		close(shell->fd_out);
	}
	else if (shell->index_cmd == 0 )
	{
		close(shell->pipefd[WRITE_END]);
		close(shell->fd_in);
		close(shell->fd_out);
	}
	else if (is_last_cmd(shell))
	{
		close (shell->pipefd[READ_END]);
		close(shell->fd_out);
		close(shell->fd_in);
	}
	else if (!is_last_cmd(shell))
	{
		close(shell->old_fd);
		close(shell->pipefd[WRITE_END]);
		close(shell->fd_out);
		close(shell->fd_in);
	}
}

void	execution_cmd(t_chill *shell)
{
	int		pid;

	shell->index_cmd = 0;
	shell->hd_count = 0;
	shell->nb_cmd = cmd_count(shell->cmd_tab);
	while (shell->cmd_tab[shell->index_cmd])
	{
		init_pipe(shell);
		expand(shell->cmd_tab[shell->index_cmd], shell->env);
		get_file(shell, shell->cmd_tab[shell->index_cmd]->redirection);
		pid = fork();
		if (pid == -1)
			return(perror("fork failed"));
		if (!pid)
		{
			redirect(shell);
			exec(shell, shell->cmd_tab[shell->index_cmd]->cmd);
		}
		else
			close_fd(shell);
		shell->index_cmd++;
	}
	wait_command(shell);
}
