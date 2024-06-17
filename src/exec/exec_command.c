/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:17:30 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/17 15:15:55 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_pipe(t_chill *shell)
{
	if (shell->nb_cmd == 1)
		return ;
	if (is_last_cmd(shell))
		return ;
	if (pipe(shell->pipefd) < 0)
	{
		print_error("pipe", strerror(errno));
		exit_shell(shell, 1);
	}
}

static void	wait_command(t_chill *shell)
{
	int	status;

	while (shell->index_cmd--)
	{
		wait(&status);
		shell->exit_status = WEXITSTATUS(status);
	}
}

static void	update_fd(t_chill *shell)
{
	if (shell->nb_cmd != 1)
	{
		close(shell->pipefd[WRITE_END]);
		if (shell->old_fd != -1)
			close(shell->old_fd);
		if (!is_last_cmd(shell))
			shell->old_fd = shell->pipefd[READ_END];
		if (is_last_cmd(shell))
			close(shell->pipefd[READ_END]);
	}
}

static void	exec_child(t_chill *shell)
{
	char	*path;
	char	**cmd;

	if (expand(shell->cmd_tab[shell->index_cmd], shell) != 0)
		exit_shell(shell, 1);
	get_file(shell, shell->cmd_tab[shell->index_cmd]->redirection);
	redirect(shell);
	cmd = shell->cmd_tab[shell->index_cmd]->cmd;
	if (!cmd | !cmd[0])
		exit_shell(shell, shell->exit_status);
	if (isbuiltin(cmd, shell))
		exit_shell(shell, 0);
	if (shell->fd_in == -1)
		close (shell->pipefd[1]);
	else
	{
		path = get_valid_path(cmd[0], shell->env);
		if (!path)
			exit_shell(shell, 127);
		execve(path, cmd, shell->env);
		exit_shell(shell, 126);
	}
	exit_shell(shell, 0);
}

/* EXECUTION PART
 * create a child for each sub command when needed.
 * Mean create a fork for each cmd in between pipe
 * Except for builtin when alone
 * */
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
		pid = fork();
		if (pid == -1)
		{
			print_error("fork", strerror(errno));
			break ;
		}
		if (pid == 0)
			exec_child(shell);
		else
			update_fd(shell);
		shell->index_cmd++;
	}
	wait_command(shell);
}
