/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:06:49 by marvin            #+#    #+#             */
/*   Updated: 2024/05/15 17:06:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    isbuiltin(char **cmd, char **env)
{
	if (!ft_strcmp(cmd[0], "env"))
		ft_env(cmd, env);
	if (!ft_strcmp(cmd[0], "cd"))
		ft_cd(cmd, env);
	if (!ft_strcmp(cmd[0], "exit"))
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	if (!ft_strcmp(cmd[0], "echo"))
		ft_echo(cmd[1]);
}
