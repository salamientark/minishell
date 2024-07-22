/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:42:38 by ple-guya          #+#    #+#             */
/*   Updated: 2024/07/18 11:52:32 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	key_match(char *line, char *env_input, int key_len)
{
	if (ft_strncmp(line, env_input, key_len) == 0
		&& (!env_input[key_len] || env_input[key_len] == EQUAL))
		return (1);
	return (0);
}

/* Add a new variable to the environment realocating the new env
 * */
static int	env_add_input(char *input, t_chill *shell)
{
	char	**new_env;
	int		index;

	new_env = (char **)malloc(sizeof(char *) * (ft_tab_size(shell->env) + 2));
	if (!new_env)
		return (print_error("malloc", strerror(errno)), 1);
	index = 0;
	while (shell->env[index])
	{
		new_env[index] = shell->env[index];
		index++;
	}
	new_env[index] = input;
	new_env[index + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	return (0);
}

/* Add a new variable to env or replace a variable in env
 * Return 1 on error
 * Return 0 on sucess
 * */
int	update_env(char *line, t_chill *shell)
{
	size_t	key_len;
	char	*line_cp;
	int		index;

	if (!line)
		return (0);
	key_len = 0;
	while (line[key_len] && line[key_len] != EQUAL)
		key_len++;
	index = 0;
	line_cp = ft_strdup(line);
	if (!line_cp)
		return (print_error("ft_strdup", "malloc error"), 1);
	while (shell->env[index])
	{
		if (key_match(line_cp, shell->env[index], key_len))
		{
			free(shell->env[index]);
			shell->env[index] = line_cp;
			return (0);
		}
		index++;
	}
	return (env_add_input(line_cp, shell));
}

/* Export variable into shell->env
 * Return 0 on success
 * 1 on Error */
int	ft_export(char **cmd, t_chill *shell)
{
	int	i;
	int	export_error;

	i = 0;
	if (!cmd[1])
		return (print_export(shell->env), 0);
	i = 1;
	export_error = 0;
	while (cmd[i])
	{
		if (!is_name(cmd[i]))
		{
			export_error = 1;
			print_error_cmd("export :", cmd[i], "not a valid identifier");
		}
		else
			export_error = export_error | update_env(cmd[i], shell);
		i++;
	}
	shell->exit_status = export_error;
	return (export_error);
}
