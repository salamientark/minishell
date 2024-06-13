/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:17:30 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/13 19:44:26 by madlab           ###   ########.fr       */
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
	int	status;

	while (shell->index_cmd--)
	{
		wait(&status);
		shell->exit_status = WEXITSTATUS(status);
	}
	printf("%d\n", shell->exit_status);
}

void	free_all(t_simple_cmd ***cmd_tab, int last_cmd)
{
	int	index;

	if (!*cmd_tab)
		return ;
	index = 0;
	while (index < last_cmd)
	{
		ft_free_char_tab(&((*cmd_tab)[index]->cmd));
		(*cmd_tab)[index]->cmd = NULL;
		ft_free_char_tab(&((*cmd_tab)[index]->redirection));
		(*cmd_tab)[index]->redirection = NULL;
		free((*cmd_tab)[index]);
		(*cmd_tab)[index] = NULL;
		index++;
	}
	while ((*cmd_tab)[index])
	{
		free((*cmd_tab)[index]);
		(*cmd_tab)[index] = NULL;
		index++;
	}
	free(*cmd_tab);
	*cmd_tab = NULL;
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
		if (!path)
			exit(127);
		execve(path, cmd, shell->env);
	}
	//free_str_tab(&cmd);
	// free_str_tab(&shell->cmd_tab[shell->index_cmd]->redirection);
	// free_str_tab(&shell->cmd_tab[shell->index_cmd]->cmd);
	free_all(&shell->cmd_tab, shell->nb_cmd);
	free_str_tab(&shell->env);
	free(shell);
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
			return (perror("fork failed"));
		if (!pid)
		{
			expand(shell->cmd_tab[shell->index_cmd], shell);
			get_file(shell, shell->cmd_tab[shell->index_cmd]->redirection);
			redirect(shell);
			exec(shell, shell->cmd_tab[shell->index_cmd]->cmd);
		}
		else
			update_fd(shell);
		shell->index_cmd++;
	}
	wait_command(shell);
}
