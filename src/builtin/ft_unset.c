/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:28:49 by ple-guya          #+#    #+#             */
/*   Updated: 2024/05/20 15:28:49 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_unset(char **cmd, char **env)
{
	char *cmd_tmp;
	int i;

	while(*cmd)
	{
		i = 0;
		cmd_tmp = ft_strjoin(*cmd, "=");
		if (!cmd_tmp)
			return(free(cmd_tmp));
		while(env[i])
		{
			if (!ft_strncmp(cmd_tmp, env[i], ft_strlen(cmd_tmp)))
				return(free(env[i]));
			i++;
		}
		cmd++;
    }
}