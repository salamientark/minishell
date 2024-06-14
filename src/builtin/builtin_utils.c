/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 17:06:49 by marvin            #+#    #+#             */
/*   Updated: 2024/06/14 10:31:38 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//check what builtin it is, execute it and return 1 
//if none has been found, return 0
int	isbuiltin(char **cmd, t_chill *shell)
{
	(void) shell;
	if (!ft_strcmp(cmd[0], "env"))
		return (1);
	if (!ft_strcmp(cmd[0], "cd"))
		return (1);
	if (!ft_strcmp(cmd[0], "exit"))
		return (1);
	if (!ft_strcmp(cmd[0], "echo"))
		return (1);
	if (!ft_strcmp(cmd[0], "pwd"))
		return (1);
	if (!ft_strcmp(cmd[0], "export"))
		return (1);
	if (!ft_strcmp(cmd[0], "unset"))
		return (1);
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
