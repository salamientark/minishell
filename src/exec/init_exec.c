/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 15:16:01 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/04 18:55:50 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void get_file(t_chill *shell)
{
	t_simple_cmd *infile;
}

void get_valid_path(t_chill *shell, char *cmd)
{
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/') && !access(cmd, F_OK | X_OK))
	{
		shell->path = cmd;
		return ;
	}
	if (!shell->cmd)
		return (clean_2dtab(shell->cmd));
	while (shell->dir[i])
	{
		shell->path = ft_strjoin(shell->dir[i], shell->cmd[0]);
		if (!shell->path)
			break ;
		if (access(shell->path, F_OK | X_OK) == 0)
			return (clean_2dtab(shell->cmd));
		else
			free(shell->path);
		i++;
	}
	shell->path = ft_strdup("");
}
