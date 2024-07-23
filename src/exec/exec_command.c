/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:17:30 by ple-guya          #+#    #+#             */
/*   Updated: 2024/07/23 16:28:52 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_exec(t_chill *shell)
{
	shell->index_cmd = 0;
	shell->hd_count = 0;
	shell->old_fd = -1;
	shell->nb_cmd = cmd_count(shell->cmd_tab);
	shell->fd_in = -1;
	shell->fd_out = -1;
}

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

static void	init_child(t_chill *shell)
{
	char	**redir;
	char	**redir_cpy;
	int		i;

	i = 0;
	redir_cpy = copy_redir(shell->cmd_tab[shell->index_cmd]->redirection);
	if (expand(shell->cmd_tab[shell->index_cmd], shell) != 0)
		exit_shell(shell, 1);
	redir = shell->cmd_tab[shell->index_cmd]->redirection;
	if (!redir_cpy)
		return ;
	while (redir_cpy[i])
	{
		printf("redir[%d] : %s || redir_cpy[%d] : %s\n", i, redir[i], i, redir_cpy[i]);
		if (!redir[i] || !redir[i][0] || (get_operator(redir_cpy[i]) != get_operator(redir[i]) && get_operator(redir_cpy[i]) == 0))
		{
			if (get_operator(redir_cpy[i]) != 0)
				i++;
			print_error(redir_cpy[i], "ambigous redirect");
			free_str_tab(&redir_cpy);
			exit_shell(shell, 1);
		}
		i++;
	}
	free_str_tab(&redir_cpy);
}

static void	child(t_chill *shell)
{
	char	**cmd;
	char	*path;

	signal(SIGQUIT, SIG_DFL);
	init_child(shell);
	get_file(shell, shell->cmd_tab[shell->index_cmd]->redirection);
	redirect(shell);
	cmd = shell->cmd_tab[shell->index_cmd]->cmd;
	if (shell->fd_in == -1)
		close (shell->pipefd[1]);
	if (!cmd || !cmd[0])
		exit_shell(shell, shell->exit_status);
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
		shell->builtin_ref = isbuiltin(shell->cmd_tab[shell->index_cmd]->cmd,
				shell);
		pid = fork();
		if (pid == -1)
		{
			print_error("fork", strerror(errno));
			break ;
		}
		if (pid == 0)
			child(shell);
		if (update_fd(shell))
			break ;
		shell->index_cmd++;
	}
	wait_command(shell, pid);
}
