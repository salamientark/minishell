/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:42:38 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/27 23:10:29 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// //check input error and return the len to malloc for the export variable
// static int	check_valid_var(char *cmd)
// {
// 	int		i;
// 	int		len;
// 	int		is_equal_sign;
// 
// 	i = 0;
// 	len = 0;
// 	is_equal_sign = 0;
// 	if (cmd[0] == '=' || ft_isdigit(cmd[0]))
// 		return (ft_putendl_fd("invalid name for export", 2), 0);
// 	while (cmd[i])
// 	{
// 		if (cmd[i] == '=')
// 			is_equal_sign = 1;
// 		if ((cmd[i] == '{' || cmd[i] == '}' || cmd[i] == '[' || cmd[i] == ']')
// 			&& !is_equal_sign)
// 			return (ft_putendl_fd("invalid name for export", 2), 0);
// 		len++;
// 		i++;
// 	}
// 	if (!is_equal_sign)
// 		return (0);
// 	return (len);
// }
// 
// static char	*get_var(char *cmd, int len)
// {
// 	char	*var_env;
// 	int		i;
// 	int		j;
// 
// 	if (len == 0)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	var_env = (char *)malloc(sizeof(char) * len + 1);
// 	if (!var_env)
// 	{
// 		perror("malloc failed");
// 		return (NULL);
// 	}
// 	while (j < len)
// 	{
// 		var_env[j++] = cmd[i];
// 		i++;
// 	}
// 	var_env[j] = '\0';
// 	return (var_env);
// }
// 
// static char	*get_var_name(char *var)
// {
// 	char	*name;
// 	int		len;
// 	int		i;
// 
// 	len = 0;
// 	i = 0;
// 	while (var[len] != '=')
// 		len++;
// 	if (var[len] != '=')
// 		return (NULL);
// 	name = (char *)malloc(len + 2);
// 	if (!name)
// 		return (NULL);
// 	while (i < len)
// 	{
// 		name[i] = var[i];
// 		i++;
// 	}
// 	name[i] = '=';
// 	name[i + 1] = '\0';
// 	return (name);
// }
// 
// static void	add_to_env(char *cmd, t_chill *shell)
// {
// 	int		len;
// 	char	*var;
// 	char	*var_name;
// 	int		i;
// 
// 	i = 0;
// 	len = check_valid_var(cmd);
// 	var = get_var(cmd, len);
// 	if (!var)
// 		return ;
// 	var_name = get_var_name(var);
// 	if (!var_name)
// 		return (free(var));
// 	while (shell->env[i])
// 	{
// 		if (!ft_strncmp(shell->env[i], var_name, ft_strlen(var_name)))
// 		{
// 			free(shell->env[i]);
// 			shell->env[i] = var;
// 			return (free(var_name));
// 		}
// 		i++;
// 	}
// 	return (update_env(shell, var), free(var_name));
// }
// 
// 
// 
// static char	*get_key(char *line)
// {
// 	size_t	key_len;
// 	char	*key;
// 
// 	while (line[key_len] && line[key_len] != EQUAL)
// 		key_len++;
// 	key = ft_strndup(line, key_len);
// 	if (!key)
// 		return (print_error("ft_strndup", "malloc error"), NULL);
// 	return (key);
// }
// 
// static int	env_replace(char *line, char *key, char *value)
// {
// 	char	*new_line;
// 	size_t	line_len;
// 
// 	if (!line || !key)
// 		return (0);
// 	line_len = ft_strlen(key);
// 	if (value)
// 		line_len += 1 + ft_strlen(key);
// 	new_line = (char *)malloc(line_len + 1);
// 	if (!new_line)
// 		return (print_error("malloc", strerror(errno)), 1);
// 	new_line[0] = '\0';
// 	new_line = ft_strcat(new_line, key);
// 	if (value)
// 	{
// 		new_line = ft_strcat(new_line, "=");
// 		new_line = ft_strcat(new_line, value);
// 	}
// 	free(line);
// 	line = new_line;
// 	return (0);
// }

// static int	add_to_env(char *line, t_chill *shell)
// {
// 	int		index;
// 	size_t	key_len;
// 	char	**env;
// 	char	*key;
// 
// 	index = 0;
// 	env = shell->env;
// 	key = get_key(line);
// 	key_len = ft_strlen(key);
// 	if (!key)
// 		return (1);
// 	while (env[index])
// 	{
// 		if (ft_strncmp(key, env[index], key_len) == 0)
// 		{
// 			if (env_replace(env[index], key, value) != 0)
// 		}
// 	}
// 
// }
// 
/* Check if the key match the key of the env input
 * key must be a name accordingly to bash standard
 * return 1 whrn there is a match
 * Return 0 when no match
 * */
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
 * 1 on Error
 * */
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
