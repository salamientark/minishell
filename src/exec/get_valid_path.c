/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_valid_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:41:48 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/08 21:24:13 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_valid_path(char *cmd, char **env)
{
	char	**dir;
	char	*path;
	int		i;
	
	i = 0;
	if (ft_strchr(cmd, '/') && !access(cmd, F_OK | X_OK))
		return(ft_strdup(cmd));
	dir = split_path(env);
	if (!dir)
		return (NULL);
	while (dir[i])
	{
		path = ft_strjoin(dir[i], cmd);
		if (!path)
			return(NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (free_str_tab(&dir), path);
		else
			free(path);
		i++;
	}
	print_error_cmd("minishell : ", cmd, "command not found");
	free_str_tab(&dir);
	exit(127);
}
