/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:57:47 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/22 17:20:36 by ple-guya         ###   ########.fr       */
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

static int	change_old_pwd(char *oldpwd, t_chill *shell, int index)
{
	char	*oldpwd_env;

	oldpwd_env = ft_strjoin("OLDPWD=", oldpwd);
	if (!oldpwd_env)
		return (print_error("ft_strjoin", "malloc error"), 1);
	free(shell->env[index]);
	shell->env[index] = oldpwd_env;
	return (0);
}

static int	change_pwd(char *oldpwd, char *newpwd, t_chill *shell)
{
	int		i;
	char	*newpwd_env;

	i = 0;
	check_for_update(shell);
	while (shell->env[i])
	{
		if (!ft_strncmp(shell->env[i], "OLDPWD=", 7)
			&& change_old_pwd(oldpwd, shell, i) != 0)
			return (1);
		if (!ft_strncmp(shell->env[i], "PWD=", 4))
		{
			newpwd_env = ft_strjoin("PWD=", newpwd);
			if (!newpwd_env)
				return (print_error("ft_strjoin", "malloc error"), 1);
			free(shell->env[i]);
			shell->env[i] = newpwd_env;
		}
		i++;
	}
	return (0);
}

int	ft_cd(char **cmd, t_chill *shell)
{
	char	oldpwd[MAX_PATHLEN];
	char	newpwd[MAX_PATHLEN];
	char	*home;

	getcwd(oldpwd, MAX_PATHLEN);
	if (!cmd[1] || !ft_strcmp(cmd[1], "~"))
	{
		home = ft_getenv("HOME", shell->env);
		if (!home)
			return(ft_putendl_fd("home not found", 2), 1);
		if (chdir(home))
			perror("cd : home");
	}
	else if (cmd[2])
		return (print_error("cd", "too many argument"), 1);
	else if (!ft_strcmp(cmd[1], "-"))
		return (ft_putendl_fd(oldpwd, 1), 0);
	else if (chdir(cmd[1]) != 0)
			return (print_error_cmd("cd :", cmd[1], strerror(errno)), 1);
	getcwd(newpwd, MAX_PATHLEN);
	make_new_prompt(shell);
	return (change_pwd(oldpwd, newpwd, shell));
}
