/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:42:34 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/11 20:51:16 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tabsize(char **tab)
{
	int	len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

char	**copy_env(char **env)
{
	char	**new_env;
	int		len;
	int		i;

	i = 0;
	len = tabsize(env);
	new_env = (char **)malloc(sizeof(char *) * (len + 1));
	if(!new_env)
		return (NULL);
	while(env[i] && i < len)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

static void	init_env(t_chill *shell)
{
	char		cwd[MAX_PATHLEN];
	char		**env;
	char		*pwd;

	getcwd(cwd, MAX_PATHLEN);
	env = (char **)malloc(sizeof(char *) * 4);
	if (!env)
		return;
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return(free(pwd));
	shell->env[0] = pwd;
	shell->env[1] = ft_strdup("SHLVL=1");
	if (!shell->env[1])
		return ;
	shell->env[2] = ft_strdup("_=usr/bin/env");
	if (!shell->env[2])
		return ;
	shell->env[3] = NULL;
}

void	init_minishell(t_chill *shell, char **env)
{
	shell->env = copy_env(env);
	if (!shell->env && !(*shell->env))
		init_env(shell);
}
