/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 16:25:32 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/08 17:26:31 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	case_no_pipe(t_chill *shell)
{
	if(shell->infile)
		dup2(shell->fd_in, STDIN_FILENO);
	if (shell->outfile)
		dup2(shell->fd_out, STDOUT_FILENO);
}

void	redirect(t_chill *shell, char **redirection)
{
	get_file(shell, redirection);
	if (shell->nb_cmd == 1)
		case_no_pipe(shell);
}
