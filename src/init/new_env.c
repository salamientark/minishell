/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:13:14 by madlab            #+#    #+#             */
/*   Updated: 2024/06/27 16:53:32 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_pwd(char **env, int *pwd_success)
{
	char	cwd[MAX_PATHLEN];
	char	*pwd;

	if (!getcwd(cwd, MAX_PATHLEN))
		return (print_error("init_shell: error retrieving current directory:\
getcwd", ": cannot access parent directories: No such file or directory"), 0);
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (print_error("ft_strjoin", "malloc error"), 1);
	*pwd_success = 1;
	env[0] = pwd;
	return (0);
}

static int	set_default_env_value(char **env, int offset)
{
	env[0 + offset] = ft_strdup("SHLVL=1");
	if (!env[0 + offset])
		return (print_error("ft_strdup", "malloc error"), free(env), 1);
	env[1 + offset] = ft_strdup("_=usr/bin/env");
	if (!env[1 + offset])
		return (print_error("ft_strdup", "malloc error"), free(env[1]),
			free(env), 1);
	env[2 + offset] = NULL;
	env[3] = NULL;
	return (0);
}

/* Init shell environment
 * Return NULL on error
 * */
char	**new_env(void)
{
	char		**env;
	int			cwd_success;

	cwd_success = 0;
	env = (char **)malloc(sizeof(char *) * 4);
	if (!env)
		return (print_error("malloc", strerror(errno)), NULL);
	if (set_pwd(env, &cwd_success) != 0)
		return (free(env), NULL);
	if (set_default_env_value(env, cwd_success) != 0)
	{
		if (cwd_success)
			free(env[0]);
		return (free(env), NULL);
	}
	return (env);
}
