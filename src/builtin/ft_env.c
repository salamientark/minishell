/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:58:19 by marvin            #+#    #+#             */
/*   Updated: 2024/05/15 16:58:19 by marvin           ###   ########.fr       */
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
	while (env[i])
		printf("%s\n", env[i++]);
}
