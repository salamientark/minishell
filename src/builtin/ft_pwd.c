/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 22:51:39 by ple-guya          #+#    #+#             */
/*   Updated: 2024/05/16 22:51:39 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **cmd)
{
	char	pwd[MAX_PATHLEN];

	if (cmd[1])
	{
		ft_putendl_fd("pwd: too many argument", 2);
		return ;
	}
	getcwd(pwd, MAX_PATHLEN);
	ft_putendl_fd(pwd, 2);
}
