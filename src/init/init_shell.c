/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:42:34 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/14 08:42:57 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Properly free env on error
 * */
static void	free_env(char ***env, int last_index)
{
	int	index;

	index = 0;
	while (index < last_index)
	{
		free((*env)[index]);
		(*env)[index] = NULL;
		index++;
	}
	free(*env);
	*env = NULL;
}

/* Init shell environment
 * Return NULL on error
 * */
static char	**new_env(void)
{
	char		cwd[MAX_PATHLEN];
	char		**env;
	char		*pwd;

	getcwd(cwd, MAX_PATHLEN);
	if (!cwd[0])
		return (print_error("cwd", strerror(errno)), NULL);
	env = (char **)malloc(sizeof(char *) * 4);
	if (!env)
		return (print_error("malloc", strerror(errno)), NULL);
	pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (print_error("ft_strjoin", "malloc error"), free(env), NULL);
	env[0] = pwd;
	env[1] = ft_strdup("SHLVL=1");
	if (!env[1])
		return (print_error("ft_strdup", "malloc error"), free(pwd), free(env),
			NULL);
	env[2] = ft_strdup("_=usr/bin/env");
	if (!env[2])
		return (print_error("ft_strdup", "malloc error"), free(env[1]),
			free(pwd), free(env), NULL);
	env[3] = NULL;
	return (env);
}

/* Get the new shlvl value
 * */
static char	*new_shlvl(char *shlvl)
{
	int		shlvl_value;
	char	*shlvl_str_val;
	char	*final_shlvl;

	shlvl_value = ft_atoi(shlvl + 6);
	if (shlvl_value == 1000)
	{
		printf("minishell: %s", SHLVL_TOO_HIGH);
		shlvl_value = 1;
	}
	else
		shlvl_value += 1;
	shlvl_str_val = ft_itoa(shlvl_value);
	if (!shlvl_str_val)
		return (print_error("ft_itoa", "malloc error"), NULL);
	final_shlvl = ft_strjoin("SHLVL=", shlvl_str_val);
	if (!final_shlvl)
		return (print_error("ft_strjoin", "malloc error"), free(shlvl_str_val),
			NULL);
	free(shlvl_str_val);
	return (final_shlvl);
}

/* Copy env updating SHLVL value
 * Return NULLL on error
 * */
static char	**copy_env(char **env)
{
	char	**new_env;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (env[len])
		len++;
	new_env = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new_env)
		return (NULL);
	while (env[i] && i < len)
	{
		if (ft_strncmp(env[i], "SHLVL=", 6) == 0)
			new_env[i] = new_shlvl(env[i]);
		else
			new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
			return (free_env(&new_env, i), NULL);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

/* Init shell copying the environment if set
 * */
t_chill	*init_shell(char **env)
{
	t_chill	*shell;

	shell = (t_chill *)malloc(sizeof(struct s_chill));
	if (!shell)
		return (print_error("malloc", strerror(errno)), NULL);
	shell->tree = NULL;
	shell->cmd_tab = NULL;
	shell->infile = NULL;
	shell->outfile = NULL;
	shell->exit_status = 0;
	if (!env)
		shell->env = new_env();
	else
		shell->env = copy_env(env);
	if (!shell->env)
		return (free(shell), NULL);
	set_signals();
	return (shell);
}
