/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 23:35:08 by ple-guya          #+#    #+#             */
/*   Updated: 2024/07/22 23:36:42 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_command(t_chill *shell, int last_pid)
{
	int	status;
	int	error;
	int	pid;

	error = 0;
	while (1)
	{
		pid = wait(&status);
		if (pid == -1)
			break ;
		if (pid != last_pid)
			continue ;
		if (WIFEXITED(status))
			error = WEXITSTATUS(status);
		if (shell->nb_cmd == 1 && shell->builtin_ref != -1)
		{
			if (shell->builtin_ref >= 4 && shell->builtin_ref <= 6)
				shell->exit_status = error;
			break ;
		}
		shell->exit_status = error;
	}
}
