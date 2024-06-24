/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:46:54 by madlab            #+#    #+#             */
/*   Updated: 2024/06/24 17:07:21 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Free shell variable and exit shell with the status code exit_status
 * */
void	exit_shell(t_chill *shell, int exit_status)
{
	rl_clear_history();
	if (shell->cmd_tab)
		free_cmd_tab(&(shell->cmd_tab));
	if (shell->env)
		ft_free_char_tab(&(shell->env));
	if (shell->infile)
		free(shell->infile);
	if (shell->outfile)
		free(shell->outfile);
	if (shell->input)
		free(shell->input);
	free(shell);
	exit(exit_status);
}
