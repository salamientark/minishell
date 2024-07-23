/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:47:13 by madlab            #+#    #+#             */
/*   Updated: 2024/07/23 14:55:25 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_heredoc_count(t_chill *shell)
{
	int	index;

	index = 0;
	while (shell->cmd_tab[shell->index_cmd]->redirection[index])
	{
		if (ft_strcmp(shell->cmd_tab[shell->index_cmd]->redirection[index],
				"<<") == 0)
			shell->hd_count++;
		index++;
	}
}

int	update_fd(t_chill *shell)
{
	int		ref;
	char	**cmd;

	ref = shell->builtin_ref;
	if (shell->nb_cmd == 1 && ref >= 0 && ref <= 3)
	{
		if (expand(shell->cmd_tab[shell->index_cmd], shell) != 0)
			return (1);
		cmd = shell->cmd_tab[shell->index_cmd]->cmd;
		shell->exit_status = shell->builtin[ref](cmd, shell);
	}
	if (shell->nb_cmd != 1)
	{
		close(shell->pipefd[WRITE_END]);
		if (shell->old_fd != -1)
			close(shell->old_fd);
		if (!is_last_cmd(shell))
			shell->old_fd = dup(shell->pipefd[READ_END]);
		close(shell->pipefd[READ_END]);
	}
	if (!shell->cmd_tab[shell->index_cmd]->redirection)
		return (0);
	update_heredoc_count(shell);
	return (0);
}
