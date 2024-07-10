/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:42:34 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/27 18:21:32 by madlab           ###   ########.fr       */
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

/* Init the builtin array of function pointer
 * */
static void	init_builtin_tab(t_chill *shell)
{
	shell->builtin[0] = &ft_cd;
	shell->builtin[1] = &ft_exit;
	shell->builtin[2] = &ft_export;
	shell->builtin[3] = &ft_unset;
	shell->builtin[4] = &ft_echo;
	shell->builtin[5] = &ft_env;
	shell->builtin[6] = &ft_pwd;
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
t_chill	*init_shell(int ac, char **av, char **env)
{
	t_chill	*shell;

	(void) ac;
	(void) av;
	shell = (t_chill *)malloc(sizeof(struct s_chill));
	if (!shell)
		return (print_error("malloc", strerror(errno)), NULL);
	shell->tree = NULL;
	shell->cmd_tab = NULL;
	shell->infile = NULL;
	shell->outfile = NULL;
	shell->fd_in = -1;
	shell->fd_out = -1;
	shell->exit_status = 0;
	init_builtin_tab(shell);
	if (!env || !env[0])
		shell->env = new_env();
	else
		shell->env = copy_env(env);
	if (!shell->env)
		return (free(shell), NULL);
	make_new_prompt(shell);
	set_signals();
	return (shell);
}
