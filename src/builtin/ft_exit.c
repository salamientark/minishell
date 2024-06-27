/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:43:01 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/27 20:18:22 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **cmd, t_chill *shell)
{
	write(1, "exit\n", 5);
	if (cmd[1])
	{
		if (!ft_isnumber(cmd[1] + (cmd[1][0] == '-' || cmd[1][0] == '+')))
		{
			print_error_cmd("exit : ", cmd[1], "numeric argument required");
			exit_shell(shell, 2);
		}
		shell->exit_status = (unsigned char)ft_atoi(cmd[1]);
	}
	if (cmd[2])
	{
		shell->exit_status = 1;
		return (ft_putendl_fd("exit: too many arguments", 2), 1);
	}
	exit_shell(shell, shell->exit_status);
	return (1);
}
