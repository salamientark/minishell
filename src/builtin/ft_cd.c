/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:57:47 by ple-guya          #+#    #+#             */
/*   Updated: 2024/05/15 20:33:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_pwd(char *oldpwd, char *newpwd, char **env)
{
	int		i;
	char 	*oldpwd_env;
	char	*newpwd_env;

	i = 0;
	while(env[i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
		{
			oldpwd_env = ft_strjoin("OLDPWD=", oldpwd);
			if (!oldpwd_env)
				return (free(oldpwd_env));
			env[i] = oldpwd_env;
		}
		if (!ft_strncmp(env[i], "PWD=", 4))
		{
			newpwd_env = ft_strjoin("PWD=", newpwd);
			if (!newpwd_env)
				return (free(newpwd_env));
			env[i] = newpwd_env;
		}
		i++;
	}
}

void	ft_cd(char **cmd, char **env)
{
	char	oldpwd[MAX_PATHLEN];
	char	newpwd[MAX_PATHLEN];
	char	*home;

	home = getenv("HOME");
	getcwd(oldpwd, MAX_PATHLEN);
	if (cmd[2])
		return ;
	else if (!cmd[1] || !ft_strcmp(cmd[1], "~"))
	{
		if (chdir(home))
			perror("cd : home");
	}
	else if (!ft_strcmp(cmd[1], "-"))
		return(ft_putendl_fd(oldpwd, 1));
	else 
	{
		if (chdir(cmd[1]))
			perror("cd :");
	}
	getcwd(newpwd, MAX_PATHLEN);
	change_pwd(oldpwd, newpwd, env);
}
