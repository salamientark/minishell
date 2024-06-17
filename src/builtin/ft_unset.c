/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:28:49 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/13 12:59:47 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_tabsize(char **tab)
{
	int	len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

static char	**realloc_env(char **env, int remove_pos, int size)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = (char **)malloc(sizeof(char *) * size);
	if (!new_env)
		return (NULL);
	while (i < remove_pos)
	{
		new_env[i] = env[i];
		i++;
	}
	free(env[i]);
	while (env[i + 1])
	{
		new_env[i] = env[i + 1];
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

static int	remove_env(t_chill *shell, char *cmd)
{
	int		i;
	int		size;
	char	**new_env;

	i = 0;
	size = ft_tabsize(shell->env);
	while (shell->env[i])
	{
		if (!ft_strncmp(cmd, shell->env[i], ft_strlen(cmd)))
		{
			new_env = realloc_env(shell->env, i, size);
			if (!new_env)
				return (1);
			free(shell->env);
			shell->env = new_env;
			return (0);
		}
		i++;
	}
	return (0);
}

int	ft_unset(char **cmd, t_chill *shell)
{
	char	*cmd_tmp;
	int		i;

	i = 1;
	if (!cmd[1])
		return(ft_putendl_fd("unset: not enough arguments", 2), 1);
	while (cmd[i])
	{
		cmd_tmp = ft_strjoin(cmd[i], "=");
		if (!cmd_tmp)
			return (1);
		if (remove_env(shell, cmd_tmp))
			return (1);
		free(cmd_tmp);
		i++;
	}
	return (0);
}
