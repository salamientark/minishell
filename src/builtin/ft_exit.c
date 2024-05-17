/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:43:01 by ple-guya          #+#    #+#             */
/*   Updated: 2024/05/16 23:43:01 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **cmd)
{
	if (cmd[1])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		return ;
	}
	write(1, "exit\n", 5);
	exit(0);
}