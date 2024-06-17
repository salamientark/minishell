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

//check what builtin it is, return the int associated with the tabfunctions
//if none has been found, return -1
int	isbuiltin(char **cmd, t_chill *shell)
{
	builtin_tab(shell);
	if (!ft_strcmp(cmd[0], "cd"))
		return (0);
	if (!ft_strcmp(cmd[0], "echo"))
		return (1);
	if (!ft_strcmp(cmd[0], "env"))
		return (2);
	if (!ft_strcmp(cmd[0], "exit"))
		return (3);
	if (!ft_strcmp(cmd[0], "unset"))
		return (4);
	if (!ft_strcmp(cmd[0], "export"))
		return (5);
	if (!ft_strcmp(cmd[0], "pwd"))
		return (6);
	return (-1);
}

void	builtin_tab(t_chill *shell)
{
	shell->builtin[0] = &ft_cd;
	shell->builtin[1] = &ft_exit;
	shell->builtin[2] = &ft_export;
	shell->builtin[3] = &ft_unset;
	shell->builtin[4] = &ft_echo;
	shell->builtin[5] = &ft_env;
	shell->builtin[6] = &ft_pwd;
}

static int	tabsize(char **tab)
{
	int	len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

char	**update_env(t_chill *shell, char *var)
{
	char	**new_env;
	int		size;
	int		i;

	i = 0;
	size = tabsize(shell->env);
	new_env = (char **)malloc((sizeof(char *) * (size + 2)));
	if (!new_env)
		return (NULL);
	while (shell->env[i])
	{
		new_env[i] = shell->env[i];
		i++;
	}
	free(shell->env);
	shell->env = new_env;
	shell->env[i] = var;
	shell->env[i + 1] = NULL;
	return (new_env);
}
