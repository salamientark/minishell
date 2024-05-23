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
int	isbuiltin(char **cmd, t_chill *shell)
{
	if (!ft_strcmp(cmd[0], "env"))
		return (ft_env(cmd, shell->env), 1);
	if (!ft_strcmp(cmd[0], "cd"))
		return (ft_cd(cmd, shell->env), 1);
	if (!ft_strcmp(cmd[0], "exit"))
		return (ft_exit(cmd), 1);
	if (!ft_strcmp(cmd[0], "echo"))
		return (ft_echo(cmd), 1);
	if (!ft_strcmp(cmd[0], "pwd"))
		return (ft_pwd(cmd), 1);
	if (!ft_strcmp(cmd[0], "export"))
		return (ft_export(cmd, shell), 1);
	if (!ft_strcmp(cmd[0], "unset"))
		return (ft_unset(cmd, shell), 1);
	return (0);
}

// int	isbuiltin(char **cmd, char **env)
// {
// 	if (!ft_strcmp(cmd[0], "cd"))
// 		return (0);
// 	if (!ft_strcmp(cmd[0], "echo"))
// 		return (1);
// 	if (!ft_strcmp(cmd[0], "env"))
// 		return (2);
// 	if (!ft_strcmp(cmd[0], "exit"))
// 		return (3);
// 	if (!ft_strcmp(cmd[0], "unset"))
// 		return (4);
// 	if (!ft_strcmp(cmd[0], "export"))
// 		return (5);
// 	if (!ft_strcmp(cmd[0], "pwd"))
// 		return (6);
// 	return (-1);
// }

/* void	**builtin_tab(void)
{
	void	*builtin_tab[7];

	builtin_tab[0] = &ft_cd;
	builtin_tab[1] = &ft_echo;
	builtin_tab[2] = &ft_env;
	builtin_tab[3] = &ft_exit;
	builtin_tab[4] = &ft_export;
	builtin_tab[5] = &ft_unset;
	builtin_tab[6] = &ft_pwd;
} */

