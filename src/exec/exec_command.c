/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:17:30 by ple-guya          #+#    #+#             */
/*   Updated: 2024/07/14 16:00:52 by ple-guya         ###   ########.fr       */
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
	int	error;
	// int	pid;

	while (shell->index_cmd--)
	{
		waitpid(0, &status, 0);
		if (WIFEXITED(status))
			error = WEXITSTATUS(status);
		if (shell->nb_cmd == 1 && shell->builtin_ref != -1)
		{
			if (shell->builtin_ref >= 4 && shell->builtin_ref <= 6)
				shell->exit_status = error;
		}
		else
			shell->exit_status = error;
	}
}

// static void	check_file_permission(t_chill *shell)
// {
// 	if (shell->fd_in == -1 && shell->index_cmd == 1 && !is_last_cmd(shell))
// 		close(shell->pipefd[READ_END]);
// 	if (shell->fd_out == -1 && is_last_cmd(shell))
// 		exit_shell(shell, 1);
// }

static void	exec_child(t_chill *shell)
{
	char	*path;
	char	**cmd;

	signal(SIGQUIT, SIG_DFL);
	get_file(shell, shell->cmd_tab[shell->index_cmd]->redirection);
	redirect(shell);
	cmd = shell->cmd_tab[shell->index_cmd]->cmd;
	if (!cmd || !cmd[0])
		exit_shell(shell, 1);
	if (shell->fd_in == -1)
		close (shell->pipefd[1]);
	if (shell->builtin_ref != -1)
		shell->exit_status = exec_builtin(cmd, shell, TRUE);
	else
	{
		path = get_valid_path(cmd[0], shell->env);
		if (!path)
			exit_shell(shell, 127);
		execve(path, cmd, shell->env);
		exit_shell(shell, 126);
	}
	exit_shell(shell, shell->exit_status);
}

void	execution_cmd(t_chill *shell)
{
	int		pid;

	init_exec(shell);
	while (shell->cmd_tab[shell->index_cmd])
	{
		init_pipe(shell);
		if (expand(shell->cmd_tab[shell->index_cmd], shell) != 0)
		{
			shell->exit_status = 1;
			break ;
		}
		shell->builtin_ref = isbuiltin(shell->cmd_tab[shell->index_cmd]->cmd,
				shell);
		pid = fork();
		if (pid == -1)
		{
			print_error("fork", strerror(errno));
			break ;
		}
		if (pid == 0)
			exec_child(shell);
		update_fd(shell);
		shell->index_cmd++;
	}
	wait_command(shell);
}
