/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:47:13 by madlab            #+#    #+#             */
/*   Updated: 2024/06/24 18:10:30 by madlab           ###   ########.fr       */
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
	if (shell->nb_cmd == 1)
	{
		if (shell->builtin_ref >= 0 && shell->builtin_ref <= 3)
			shell->builtin[shell->builtin_ref]
				(shell->cmd_tab[shell->index_cmd]->cmd, shell);
	}
	if (shell->nb_cmd != 1)
	{
		close(shell->pipefd[WRITE_END]);
		if (shell->old_fd != -1)
			close(shell->old_fd);
		if (!is_last_cmd(shell))
			shell->old_fd = shell->pipefd[READ_END];
		if (is_last_cmd(shell))
			close(shell->pipefd[READ_END]);
	}
	if (!shell->cmd_tab[shell->index_cmd]->redirection)
		return ;
	update_heredoc_count(shell);
}
