/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 21:23:25 by madlab            #+#    #+#             */
/*   Updated: 2024/06/27 23:13:29 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export_line(char *env_line)
{
	int	i;

	i = 0;
	write(1, "export ", 7);
	while (env_line[i] && env_line[i] != EQUAL)
		i++;
	write(1, env_line, i);
	if (!env_line[i])
		return ((void) write(1, "\n", 1));
	write(1, "=\"", 2);
	i += (env_line[i] && env_line[i] == EQUAL);
	while (env_line[i])
	{
		if (env_line[i] == SINGLE_QUOTE || env_line[i] == DOUBLE_QUOTE
			|| env_line[i] == '\\')
			write(1, "\\", 1);
		write(1, env_line + i, 1);
		i++;
	}
	write(1, "\"\n", 2);
}

void	print_export(char **env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "_=", 2) != 0)
			print_export_line(env[i]);
		i++;
	}
}
