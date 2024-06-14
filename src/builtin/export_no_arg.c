/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:46:14 by madlab            #+#    #+#             */
/*   Updated: 2024/06/14 15:50:38 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	case_noargs(char **env)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = 1;
		while (env[j])
		{
			if (ft_strcmp(env[j], env[j - 1]) < 0)
			{
				tmp = env[j - 1];
				env[j - 1] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (env[i])
		printf("export %s\n", env[i++]);
}
