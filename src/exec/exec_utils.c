/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:41:48 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/18 19:34:48 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(char **cmd, t_chill *shell)
{
	int ref;

	ref = shell->builtin_ref;
	if (shell->nb_cmd == 1)
	{
		if (ref >= 4 && ref <= 6)
			return (shell->builtin[ref](cmd, shell));
	}
	else
		return (shell->builtin[ref](cmd, shell));
	return(0);
}

void init_exec(t_chill *shell)
{
	shell->index_cmd = 0;
	shell->hd_count = 0;
	shell->old_fd = -1;
	shell->nb_cmd = cmd_count(shell->cmd_tab);
}

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

char	*get_valid_path(char *cmd, char **env)
{
	char	**dir;
	char	*path;
	int		i;

	i = 0;
	if (ft_strchr(cmd, '/') && !access(cmd, F_OK | X_OK))
		return (ft_strdup(cmd));
	dir = split_path(env);
	if (!dir)
		return (NULL);
	while (dir[i])
	{
		path = ft_strjoin(dir[i], cmd);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (free_str_tab(&dir), path);
		else
			free(path);
		i++;
	}
	print_error(cmd, "command not found");
	free_str_tab(&dir);
	return (NULL);
}
