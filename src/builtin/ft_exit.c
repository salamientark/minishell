/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:43:01 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/14 07:57:02 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **cmd, t_chill *shell)
{
	if (cmd[1])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return (1);
	}
	write(1, "exit\n", 5);
	exit(exit_shell(shell, 0));
	return (1);
}
