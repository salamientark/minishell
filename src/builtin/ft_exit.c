/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:43:01 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/14 11:30:34 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **cmd, t_chill *shell)
{
	if (ft_isdigit(cmd[1][0]))
	{
		if (cmd[2])
			return(ft_putendl_fd("exit : too many argument", 2), 2);
		else
			exit(cmd[1][0] + '0');
	}
	write(1, "exit\n", 5);
	exit_shell(shell, 0);
	return (1);
}
