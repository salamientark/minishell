/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:57:37 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/27 17:03:05 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal;

static void	update_prompt_exit_status(t_chill *shell)
{
	int	index;

	index = 0;
	while (shell->prompt[index] != '\0')
		index++;
	index -= 16;
	if (shell->exit_status == 0)
		shell->prompt[index] = '2';
	else
		shell->prompt[index] = '1';
}

char	*read_command(t_chill *shell)
{
	char	*input;

	g_signal = 0;
	unlink_here_doc();
	update_prompt_exit_status(shell);
	input = readline(shell->prompt);
	if (input && *input)
		add_history(input);
	return (input);
}
