/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:17:30 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/08 17:23:36 by ple-guya         ###   ########.fr       */
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
//	print_cmd(cmd);
	// if (shell->fd_in == -1)
	// 	close (shell->pipefd[1]);
	execve(path, cmd, shell->env);
	free(path);
}

void	execution_cmd(t_chill *shell)
{
	int		pid;

	shell->index_cmd = 0;
	shell->nb_cmd = cmd_count(shell->cmd_tab);
	while (shell->cmd_tab[shell->index_cmd])
	{
		printf("%d\n", shell->index_cmd);
		if (shell->nb_cmd != 1 || shell->index_cmd +1 == shell->nb_cmd)
		{
			if (pipe(shell->pipefd))
				return(perror("pipe"));
		}
		pid = fork();
		if (pid == -1)
			return(perror("fork failed"));
		if (!pid)
		{
			redirect(shell, shell->cmd_tab[shell->index_cmd]->redirection);
			exec(shell, shell->cmd_tab[shell->index_cmd]->cmd);
		}
		shell->index_cmd++;
	}
	wait(NULL);
}
