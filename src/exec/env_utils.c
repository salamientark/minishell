/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:32:53 by ple-guya          #+#    #+#             */
/*   Updated: 2024/05/22 17:32:53 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tabsize(char **tab)
{
	int len;

	len = 0;
	while (tab[len])
		len++;
	return(len);
}

char	**copy_env(char **env)
{
	char	**new_env;
	int		len;
	int		i;

	len = tabsize(env);
	if(!(new_env = (char **)malloc(sizeof(char *) * (len + 1))))
		return(free(new_env), NULL);
	while(env[i] && i < len)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
