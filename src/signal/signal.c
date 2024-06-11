/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 23:03:14 by madlab            #+#    #+#             */
/*   Updated: 2024/06/11 06:25:31 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

extern int	g_exit_status;

/* Handle here_doc signal
 * */
void	heredoc_sig_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 130;
		close(STDIN_FILENO);
	}
}

/* Habdle Ctrl+C to just give the prompt back
 * */
void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_exit_status = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/* Set default signals on initialisation
 * setting Ctrl+\ (SIGQUIT) to nothing
 * */
void	set_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
}
