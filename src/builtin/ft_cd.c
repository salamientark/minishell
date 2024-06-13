/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:57:47 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/13 13:00:52 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_for_update(t_chill *shell)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = "OLDPWD";
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], tmp, 7))
			return ;
		i++;
	}
	update_env(shell, tmp);
}

static void	change_pwd(char *oldpwd, char *newpwd, t_chill *shell)
{
	int		i;
	char	*oldpwd_env;
	char	*newpwd_env;

	i = 0;
	check_for_update(shell);
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], "OLDPWD=", 7))
		{
			oldpwd_env = ft_strjoin("OLDPWD=", oldpwd);
			if (!oldpwd_env)
				return (free(oldpwd_env));
			shell->env[i] = oldpwd_env;
		}
		if (!ft_strncmp(shell->env[i], "PWD=", 4))
		{
			newpwd_env = ft_strjoin("PWD=", newpwd);
			if (!newpwd_env)
				return (free(newpwd_env));
			shell->env[i] = newpwd_env;
		}
		i++;
	}
}

void	ft_cd(char **cmd, t_chill *shell)
{
	char	oldpwd[MAX_PATHLEN];
	char	newpwd[MAX_PATHLEN];
	char	*home;

	home = getenv("HOME");
	if (!home)
		return (ft_putendl_fd("home not found", 2));
	getcwd(oldpwd, MAX_PATHLEN);
	if (cmd[2])
		return ;
	else if (!cmd[1] || !ft_strcmp(cmd[1], "~"))
	{
		if (chdir(home))
			perror("cd : home");
	}
	else if (!ft_strcmp(cmd[1], "-"))
		return (ft_putendl_fd(oldpwd, 1));
	else
	{
		if (chdir(cmd[1]))
			perror("cd :");
	}
	getcwd(newpwd, MAX_PATHLEN);
	change_pwd(oldpwd, newpwd, shell);
}
