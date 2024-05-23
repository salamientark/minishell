/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:28:49 by ple-guya          #+#    #+#             */
/*   Updated: 2024/05/20 15:28:49 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_tabsize(char **tab)
{
	int len;

	len = 0;
	while (tab[len])
		len++;
	return(len);
}

static char **remove_env(char **env, int remove_pos, int size)
{
	char	**new_env;
	int		i;

	i = 0;
	if (!(new_env = (char**)malloc(sizeof(char *) * size)))
		return(NULL);
	while (i < remove_pos)
	{
		new_env[i] = env[i];
		i++;
	}
	free(env[i]);
	while(env[i + 1])
	{
		new_env[i] = env[i + 1];
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int	ft_unset(char **cmd, t_chill *shell)
{
	char *cmd_tmp;
	int i;
	int	size;
	int j = 1;
	char **new_env;

	size = ft_tabsize(shell->env);
	while(cmd[j])
	{
		i = 0;
		cmd_tmp = ft_strjoin(cmd[j], "=");
		if (!cmd_tmp)
			return(1);
		while(shell->env[i])
		{
			if (!ft_strncmp(cmd_tmp, shell->env[i], ft_strlen(cmd_tmp)))
			{
				new_env = remove_env(shell->env, i, size);
				if (!new_env)
					return (1);
				free(shell->env);
				shell->env = new_env;
				size--;
				break;
			}
			i++;
		}
		free(cmd_tmp);
		j++;
	}
	//shell->env[i] = NULL;
	return (0);
}
