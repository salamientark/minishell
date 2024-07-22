/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:47:13 by madlab            #+#    #+#             */
/*   Updated: 2024/07/22 19:35:20 by ple-guya         ###   ########.fr       */
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

void	update_fd(t_chill *shell)
{
	int		ref;
	char	**cmd;

	cmd = shell->cmd_tab[shell->index_cmd]->cmd;
	if(shell->nb_cmd == 1 && shell->builtin_ref != -1)
	{
		expand(shell->cmd_tab[shell->index_cmd], shell);
		ref = shell->builtin_ref;
		if (ref >= 0 && ref <= 3)
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
		return ;
	update_heredoc_count(shell);
}
