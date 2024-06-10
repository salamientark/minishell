/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:17:30 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/10 15:16:30 by ple-guya         ###   ########.fr       */
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
	if (shell->index_cmd == 0)
	{
		if (pipe(shell->pipefd))
			return(perror("pipe"));
	}
	else if (!is_last_cmd(shell))
	{
		shell->old_fd = shell->pipefd[READ_END];
		if (pipe(shell->pipefd))
			return(perror("pipe"));
	}
}

int	is_last_cmd(t_chill *shell)
{
	if (shell->nb_cmd -1 == shell->index_cmd)
		return(1);
	return(0);
}
// static void print_cmd(char **cmd)
// {
// 	int i = 0;
// 	while(cmd[i])
// 		printf("%s\n", cmd[i++]);
// 	printf("====================\n");
// }

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
	if (shell->index_cmd == 0 && shell->nb_cmd != 1)
	{
		close(shell->pipefd[WRITE_END]);
		if (shell->infile)
			close(shell->fd_in);
		if (shell->outfile)
			close(shell->fd_out);
	}
	else if (!is_last_cmd(shell))
	{
		close(shell->old_fd);
		close(shell->pipefd[READ_END]);
		if (shell->infile)
			close(shell->fd_in);
		if (shell->outfile)
			close(shell->fd_out);
	}
	else if (is_last_cmd(shell) && shell->nb_cmd != 1)
	{
		close (shell->pipefd[WRITE_END]);
		if (shell->infile)
			close(shell->fd_in);
		if (shell->outfile)
			close(shell->fd_out);
	}
}

void	execution_cmd(t_chill *shell)
{
	int		pid;

	shell->index_cmd = 0;
	shell->nb_cmd = cmd_count(shell->cmd_tab);
	while (shell->cmd_tab[shell->index_cmd])
	{
		init_pipe(shell);
		get_file(shell, shell->cmd_tab[shell->index_cmd]->redirection);
		pid = fork();
		if (pid == -1)
			return(perror("fork failed"));
		if (!pid)
		{
			expand(shell->cmd_tab[shell->index_cmd], shell->env);
			redirect(shell);
			exec(shell, shell->cmd_tab[shell->index_cmd]->cmd);
		}
		else
			close_fd(shell);
		shell->index_cmd++;
	}
	while (shell->index_cmd--)
		wait(0);
}
