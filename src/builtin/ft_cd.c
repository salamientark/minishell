/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:57:47 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/27 16:53:16 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_for_update(t_chill *shell)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup("OLDPWD");
	if (!tmp)
		return ;
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], tmp, 7))
			return (free(tmp));
		i++;
	}
	update_env(shell, tmp);
}

static int	change_pwd(char *oldpwd, char *newpwd, t_chill *shell)
{
	int		i;
	char	*tmp_pwd;

	i = 0;
	while (shell->env[i])
	{
		if ((ft_strncmp(shell->env[i], "OLDPWD=", 7) == 0 && (oldpwd[0] != '\0'
					|| ft_getenv("OLDPWD", shell->env) != NULL))
			|| (ft_strncmp(shell->env[i], "PWD=", 4) == 0 && (newpwd[0] != '\0'
					|| ft_getenv("PWD", shell->env) != NULL)))
		{
			if (!ft_strncmp(shell->env[i], "OLDPWD=", 7))
				tmp_pwd = ft_strjoin("OLDPWD=", oldpwd);
			else
				tmp_pwd = ft_strjoin("PWD=", newpwd);
			if (!tmp_pwd)
				return (print_error("ft_strjoin", "malloc error"), 1);
			free(shell->env[i]);
			shell->env[i] = tmp_pwd;
		}
		i++;
	}
	return (0);
}

static int	go_home(char *oldpwd, t_chill *shell)
{
	char	newpwd[MAX_PATHLEN];
	char	*home;

	ft_memset(newpwd, 0, MAX_PATHLEN);
	home = ft_getenv("HOME", shell->env);
	if (!home)
		return (print_error("cd", "home not found"), 2);
	if (!home)
		return (1);
	if (chdir(home) != 0)
		return (print_error("cd", strerror(errno)), 1);
	if (getcwd(newpwd, MAX_PATHLEN) == NULL)
		print_error("getcwd", strerror(errno));
	make_new_prompt(shell);
	return (change_pwd(oldpwd, newpwd, shell));
}

static int	go_last_pwd(char *oldpwd, t_chill *shell)
{
	char	newpwd[MAX_PATHLEN];
	char	*env_oldpwd;

	ft_memset(newpwd, 0, MAX_PATHLEN);
	env_oldpwd = ft_getenv("OLDPWD", shell->env);
	if (!env_oldpwd)
		return (print_error("cd", "OLDPWD not set"), 1);
	if (chdir(env_oldpwd) != 0)
		return (print_error_cmd("cd", env_oldpwd, strerror(errno)), 1);
	if (getcwd(newpwd, MAX_PATHLEN) == NULL)
		print_error("getcwd", strerror(errno));
	make_new_prompt(shell);
	return (change_pwd(oldpwd, newpwd, shell));
}

int	ft_cd(char **cmd, t_chill *shell)
{
	char	oldpwd[MAX_PATHLEN];
	char	newpwd[MAX_PATHLEN];

	ft_memset(oldpwd, 0, MAX_PATHLEN);
	ft_memset(newpwd, 0, MAX_PATHLEN);
	if (cmd[1] && cmd[2])
		return (print_error("cd", "too many arguments"), 1);
	if (getcwd(oldpwd, MAX_PATHLEN) == NULL)
		print_error("getcwd", strerror(errno));
	if (!cmd[1] || !ft_strcmp(cmd[1], "~"))
		return (go_home(oldpwd, shell));
	if (!ft_strcmp(cmd[1], "-"))
		return (go_last_pwd(oldpwd, shell));
	if (getcwd(newpwd, MAX_PATHLEN) == NULL)
		print_error("getcwd", strerror(errno));
	if (chdir(cmd[1]) != 0)
		return (print_error_cmd("cd :", cmd[1], strerror(errno)), 1);
	make_new_prompt(shell);
	return (change_pwd(oldpwd, newpwd, shell));
}
