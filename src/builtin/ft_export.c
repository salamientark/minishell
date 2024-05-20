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

static char	*get_name(char *cmd)
{
	char	*name;
	char	*cmd_env;
	
 	cmd_env = ft_strchr(cmd, '=');
	if (!cmd_env)
		name = cmd;
	else 
	{
		while(cmd[i] != '=')
		{
			if 
			name[i] = cmd[i]

		}
	}
	
}

static void	add_to_env(char *cmd, char **env)wsl

{
	char *name;

	name = get_name(cmd);

}

void	ft_export(char **cmd, char **env)
{
	int i;

	i = 0;
	if (!cmd[1])
		return (case_noarg(env));
	while(cmd[i])
	{
		check_name(cmd[i]);
		add_to_env(cmd[i], env);
	}
}