/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:41:48 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/14 10:31:53 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtin(t_chill *shell)
{
	char	**cmd;

	if (expand(shell->cmd_tab[shell->index_cmd], shell) != 0)
		return (shell->exit_status);
	get_file(shell, shell->cmd_tab[shell->index_cmd]->redirection);
	redirect(shell);
	cmd = shell->cmd_tab[0]->cmd;
	if (!ft_strcmp(cmd[0], "env"))
		return (ft_env(cmd, shell->env));
	if (!ft_strcmp(cmd[0], "cd"))
		return (ft_cd(cmd, shell));
	if (!ft_strcmp(cmd[0], "exit"))
		return (ft_exit(cmd, shell));
	if (!ft_strcmp(cmd[0], "echo"))
		return (ft_echo(cmd, shell));
	if (!ft_strcmp(cmd[0], "pwd"))
		return (ft_pwd(cmd));
	if (!ft_strcmp(cmd[0], "export"))
		return (ft_export(cmd, shell));
	if (!ft_strcmp(cmd[0], "unset"))
		return (ft_unset(cmd, shell));
	return (1);
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
	print_error_cmd("minishell : ", cmd, "command not found");
	free_str_tab(&dir);
	return (NULL);
}
