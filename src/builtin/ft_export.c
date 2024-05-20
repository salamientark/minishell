/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:42:38 by ple-guya          #+#    #+#             */
/*   Updated: 2024/05/16 23:42:38 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	case_noarg(char **env)
{
	int i;

	i = 0;
	while(env[i])
		printf("export %s\n", env[i++]);
}

//check input error and return the len to malloc for the export variable
static int	check_valid_var(char *cmd)
{
	int		i;
	int		len;
	int		is_equal_sign;

	i = 0;
	len = 0;
	is_equal_sign = 0;
	if (cmd[0] == '=')
		return(ft_putendl_fd("invalid name for export", 2), 0);
	while (cmd[i])
	{
		if (cmd[i] == '=')
			is_equal_sign = 1;
		if ((cmd[i] == SINGLE_QUOTE || cmd[i] == DOUBLE_QUOTE) && cmd[i])
			i++;
		if ((cmd[i] == '{' || cmd[i] == '}' || cmd[i] == '[' || cmd[i] == ']') 
			&&  !is_equal_sign)
		{
			ft_putendl_fd("invalid name for export", 2);
			return (0);
		}
		len++;
		i++;
	}
	if(!is_equal_sign)
		return (0);
	return(len);
}

static char	*get_var(char *cmd, int len)
{
	char	*var_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	var_env = (char *)malloc(sizeof(char) * len + 1);
	if (!var_env)
	{
		perror("malloc failed");
		return (free(var_env), NULL);
	}
	while(j < len)
	{
		if (cmd[i] == '"' || cmd[i] == '\'')
			i++;
		var_env[j++] = cmd[i];
		i++;
	}
	var_env[j] = '\0';
	return(var_env);
}

static char	*get_var_name(char *var)
{
	char	*name;
	int		len;
	int		i;

	len = 0;
	i = 0;
	while (var[len] != '=' && var[len])
		len++;
	if (var[len] != '=')
		return(NULL);
	name = (char*)malloc(len + 1);
	if(!name)
		return(NULL);
	while (i < len)
	{
		name[i] = var[i];
		i++;
	}
	return (name);
}

static void	add_to_env(char *cmd, char **env)
{
	int		len;
	char	*var;
	char	*var_name;
	int		i;

	i = 0;
	len = check_valid_var(cmd);
	if (!len)
		return ;
	var = get_var(cmd, len);
	var_name = get_var_name(var);
	while(env[i])
	{
		if(!ft_strncmp(env[i], var_name, ft_strlen(var_name)))
		{
			env[i] = var;
			return ;
		}
		i++;
	}
	env[i] = var;
}

void	ft_export(char **cmd, char **env)
{
	int i;

	i = 1;
	if (!cmd[i])
		return (case_noarg(env));
	while(cmd[i])
	{
		add_to_env(cmd[i], env);
		i++;
	}
}

