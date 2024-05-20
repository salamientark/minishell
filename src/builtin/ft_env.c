/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:43:25 by ple-guya          #+#    #+#             */
/*   Updated: 2024/05/16 23:43:25 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_error(char *cmd)
{
	write(2, "env: '", 6);
	write(2, cmd, ft_strlen(cmd));
	ft_putendl_fd("': No such file or directory", 2);
}

void	ft_env(char **cmd, char **env)
{
	int	i;

	i = 0;
	if (cmd[1])
	{
		env_error(cmd[1]);
		return ;
	}
	while (env[i + 1])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

