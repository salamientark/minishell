/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 17:17:30 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/05 20:04:22 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void print_cmd(char **cmd)
{
	int i = 0;
	while(cmd[i])
		printf("%s\n", cmd[i++]);
	printf("====================\n");
}

static void exec(t_chill *shell, char **cmd)
{
	init_redirections(shell, shell->cmd_tab[i]->redirection);
	path = get_valid_path(*shell->cmd_tab[i]->cmd, shell->env);
	print_cmd(shell->cmd_tab[i]->cmd);
	i++;
}

void	execution_cmd(t_chill *shell)
{
	char	**cmd;
	char	*path;
	int		pid;
	int		i;

	i = 0;
	
	while (shell->cmd_tab[i])
	{
		if (pipe(shell->pipefd[2]))
			return(perror("pipe"));
		pid = fork();
		if (pid == -1)
			return(perror("fork failed"));
		if (!pid)
		{
			redirect(shell, shell->cmd_tab[i]->redirection);
			exec(shell, shell->cmd_tab[i]->cmd);
		}
		close(shell->pipefd[1]);
		if (dup2(shell->pipefd[0], STDIN_FILENO) < 0)
			return(perror("dup2"));
		close(shell->pipefd[0]);
		i++;
	}
}
