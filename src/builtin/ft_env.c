/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 23:43:25 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/15 13:26:08 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_error(char *cmd)
{
	write(2, "env: '", 6);
	write(2, cmd, ft_strlen(cmd));
	ft_putendl_fd("': No such file or directory", 2);
}

int	ft_env(char **cmd, t_chill *shell)
{
	int		i;
	char	**env;

	i = 0;
	env = shell->env;
	if (cmd[1])
	{
		env_error(cmd[1]);
		return (1);
	}
	while (env[i])
	{
		if (ft_strchr(env[i], '/'))
			ft_putendl_fd(env[i], 1);
		i++;
	}
	return (0);
}
