/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:41:48 by ple-guya          #+#    #+#             */
/*   Updated: 2024/07/23 17:10:51 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_last_cmd(t_chill *shell)
{
	if (shell->nb_cmd -1 == shell->index_cmd)
		return (1);
	return (0);
}

int	cmd_count(t_simple_cmd **cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
		i++;
	return (i);
}

int	exec_builtin(char **cmd, t_chill *shell, bool write)
{
	int	ref;

	ref = shell->builtin_ref;
	if (shell->nb_cmd == 1 && write == TRUE)
	{
		if (ref >= 4 && ref <= 6)
			return (shell->builtin[ref](cmd, shell));
	}
	else
		return (shell->builtin[ref](cmd, shell));
	return (-1);
}

static void	path_error(char *cmd, char **dir)
{
	if (ft_strchr(cmd, '/'))
		return (print_error(cmd, "no such file or directory"));
	print_error(cmd, "command not found");
	free_str_tab(&dir);
}

char	*get_valid_path(char *cmd, t_chill *shell)
{
	char	**dir;
	char	*path;
	int		i;

	i = 0;
	path = preliminary_path(cmd, shell);
	if (path != NULL)
		return (path);
	dir = split_path(shell->env);
	if (!dir)
		return (NULL);
	while (dir[i])
	{
		path = ft_strjoin(dir[i++], cmd);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (free_str_tab(&dir), path);
		else
			free(path);
	}
	path_error(cmd, dir);
	return (NULL);
}
