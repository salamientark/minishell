/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:43:01 by ple-guya          #+#    #+#             */
/*   Updated: 2024/07/18 11:58:55 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	case_arg(char *cmd, t_chill *shell)
{
	int				i;
	unsigned int	exit_code;

	i = 0;
	if (cmd[i] == '-' || cmd[i] == '+')
		i++;
	while (cmd[i])
	{
		if (!ft_isdigit(cmd[i]))
		{
			print_error_cmd("exit : ", cmd, "numeric argument required");
			exit_shell(shell, 2);
		}
		i++;
	}
	exit_code = ft_atoi(cmd);
	return (exit_code);
}

int	ft_exit(char **cmd, t_chill *shell)
{
	write(1, "exit\n", 5);
	if (cmd[1])
	{
		if (cmd[1][0] == 0 || (cmd[1][0] == '+' && !ft_isdigit(cmd[1][1]))
			|| !ft_isnumber(cmd[1] + (cmd[1][0] == '+')))
		{
			print_error_cmd("minishell: exit: ", cmd[1], "numeric argument required");
			exit_shell(shell, 2);
		}
		shell->exit_status = (unsigned char)ft_atoi(cmd[1]);
	}
	if (cmd[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		shell->exit_status = 1;
	}
	else
		exit_shell(shell, shell->exit_status);
	return (shell->exit_status);
}
