/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:46:40 by dbaladro          #+#    #+#             */
/*   Updated: 2024/06/13 19:40:15 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

int	main(int ac, char **av, char **env)
{
	t_chill			*shell;

	(void) ac;
	(void) av;
	shell = init_shell(env);
	if (!shell)
		return (1);
	while ("this is the best minishell")
	{
		unlink_here_doc();
		shell->input = display_prompt();
		if (!shell->input)
			break ;
		if (ft_strlen(shell->input) > 0)
		{
			shell->cmd_tab = parse_input(shell->input, shell);
			if (shell->cmd_tab)
			{
				free_cmd_tab(&shell->cmd_tab);
			}
		}
		free(shell->input);
	}
	return (exit_shell(shell, 0));
}
