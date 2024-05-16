/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 16:57:47 by ple-guya          #+#    #+#             */
/*   Updated: 2024/05/15 02:38:09 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_old_pwd()
{
	
}

static void	change_pwd()
{
	
}

void	cd(char *dir, char **env)
{
	char	*home;
	char	*oldpwd;
	char	pwd[100];
	(void)env;
	oldpwd = getenv("OLDPWD");
	if (!dir)
	{
		home = getenv("HOME");
		if (chdir(home))
			perror("cd");
		return ;
	}
	if (!ft_strcmp(dir, "-"))
	{
		if(chdir(oldpwd))
			perror("cd");
		printf(oldpwd);
	}
	
}
