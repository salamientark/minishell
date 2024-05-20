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

//check what builtin it is, execute it and return 1 
//if none has been found, return 0
int	isbuiltin(char **cmd, char **env)
{
	if (!ft_strcmp(cmd[0], "env"))
		return (ft_env(cmd, env), 1);
	if (!ft_strcmp(cmd[0], "cd"))
		return (ft_cd(cmd, env), 1);
	if (!ft_strcmp(cmd[0], "exit"))
		return (ft_exit(cmd), 1);
	if (!ft_strcmp(cmd[0], "echo"))
		return (ft_echo(cmd), 1);
	if (!ft_strcmp(cmd[0], "pwd"))
		return (ft_pwd(cmd), 1);
	if (!ft_strcmp(cmd[0], "export"))
		ft_export(cmd, env);
	// if (!ft_strcmp(cmd[0], "unset"))
	// 	ft_unset(cmd);
	return (0);
}
