/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:06:49 by marvin            #+#    #+#             */
/*   Updated: 2024/06/27 23:05:31 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isbuiltin(char **cmd, t_chill *shell)
{
	(void) shell;
	if (!cmd || !cmd[0])
		return (-1);
	if (!ft_strcmp(cmd[0], "cd"))
		return (0);
	if (!ft_strcmp(cmd[0], "exit"))
		return (1);
	if (!ft_strcmp(cmd[0], "export"))
		return (2);
	if (!ft_strcmp(cmd[0], "unset"))
		return (3);
	if (!ft_strcmp(cmd[0], "echo"))
		return (4);
	if (!ft_strcmp(cmd[0], "env"))
		return (5);
	if (!ft_strcmp(cmd[0], "pwd"))
		return (6);
	return (-1);
}

// static int	tabsize(char **tab)
// {
// 	int	len;
// 
// 	len = 0;
// 	while (tab[len])
// 		len++;
// 	return (len);
// }

// char	**update_env(t_chill *shell, char *var)
// {
// 	char	**new_env;
// 	int		size;
// 	int		i;
// 
// 	i = 0;
// 	size = tabsize(shell->env);
// 	new_env = (char **)malloc((sizeof(char *) * (size + 2)));
// 	if (!new_env)
// 		return (NULL);
// 	while (shell->env[i])
// 	{
// 		new_env[i] = shell->env[i];
// 		i++;
// 	}
// 	free(shell->env);
// 	shell->env = new_env;
// 	shell->env[i] = var;
// 	shell->env[i + 1] = NULL;
// 	return (new_env);
// }
