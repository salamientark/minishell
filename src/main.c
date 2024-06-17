/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:46:40 by dbaladro          #+#    #+#             */
/*   Updated: 2024/06/17 15:14:45 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

int	main(int ac, char **av, char **env)
{
	t_chill			*shell;

	shell = init_shell(ac, av, env);
	if (!shell)
		return (1);
	while ("this is the best minishell")
	{
		unlink_here_doc();
		shell->input = read_command(shell);
		if (!shell->input)
			break ;
		if (ft_strlen(shell->input) > 0)
		{
			shell->cmd_tab = parse_input(shell->input, shell);
			execution_cmd(shell);
			free_cmd_tab(&shell->cmd_tab);
		}
		free(shell->input);
	}
	exit_shell(shell, shell->exit_status);
}
