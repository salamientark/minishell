/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:57:47 by ple-guya          #+#    #+#             */
/*   Updated: 2024/05/14 23:28:13 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static int	check_absolute_dir(char *dir)
{
	if (ft_strchr(dir, '/') && !access(dir, F_OK))
	{
		return (1);
	}
	return(0);
} */

void	cd(char *dir)
{
	// if (check_absolute_dir(dir))
	// {
		if (chdir(dir))
			perror("cd ");
		else
			return;
}
