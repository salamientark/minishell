/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:17:30 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/11 22:41:49 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_pipe(t_chill *shell)
{
	if (shell->nb_cmd == 1)
		return ;
	if (is_last_cmd(shell))
		return;
	if (pipe(shell->pipefd) < 0)
	{
		perror("pipe");
		exit(1);
	}
}

static void	wait_command(t_chill *shell)
{
	while (shell->index_cmd--)
	{
		wait(&shell->exit_status);

		shell->error_code = WEXITSTATUS(shell->exit_status);
	}
}

static void	exec(t_chill *shell, char **cmd)
{
	char	*path;

	if (shell->fd_in == -1)
		close (shell->pipefd[1]);
	if (isbuiltin(cmd, shell))
		exit(0);
	else
	{
		path = get_valid_path(*cmd, shell->env);
		if (!path || access(path, X_OK | F_OK))
			exit(1);
		execve(path, cmd, shell->env);
	}
}

static void	update_fd(t_chill *shell)
{
	if (shell->nb_cmd != 1)
	{
		close(shell->pipefd[WRITE_END]);
		if (shell->old_fd != 1)
			close(shell->old_fd);
		if (!is_last_cmd(shell))
			shell->old_fd = shell->pipefd[READ_END];
	}
}

void	execution_cmd(t_chill *shell)
{
	int		pid;

	shell->index_cmd = 0;
	shell->hd_count = 0;
	shell->old_fd = -1;
	shell->nb_cmd = cmd_count(shell->cmd_tab);
	while (shell->cmd_tab[shell->index_cmd])
	{
		init_pipe(shell);
		expand(shell->cmd_tab[shell->index_cmd], shell->env);
		pid = fork();
		if (pid == -1)
			return (perror("fork failed"));
		if (!pid)
		{
			get_file(shell, shell->cmd_tab[shell->index_cmd]->redirection);
			redirect(shell);
			exec(shell, shell->cmd_tab[shell->index_cmd]->cmd);
		}
		else
			update_fd(shell);
		shell->index_cmd++;
	}
	if (shell->nb_cmd != 1)
		close(shell->pipefd[READ_END]);
	wait_command(shell);
}
