/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:57:47 by ple-guya          #+#    #+#             */
/*   Updated: 2024/05/14 18:21:08 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_absolute_path(char *path)
{
	if (ft_strchr(path, '/') && !access(path, F_OK))
	{
		return (1);
	}
	return(0);
}

void	cd(char *path)
{
	if (check_absolute_path(path))
	{
		if (chdir(path))
			perror("cd ");
	}
	else
	{
		chdir(path);
	}
}