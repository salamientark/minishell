/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:46:40 by dbaladro          #+#    #+#             */
/*   Updated: 2024/06/14 10:34:20 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

int	g_signal;

static int	is_input_valid(t_chill *shell)
{
	if (heredoc_count(shell->input) > 16)
	{
		write(2, HERE_DOC_COUNT_EXCEEDED, 48);
		exit(exit_shell(shell, 1));
	}
	if (unclosed_delimiter(shell->input))
	{
		shell->exit_status = 1;
		return (0);
	}
	if (syntax_error(shell->input, shell))
	{
		shell->exit_status = 2;
		return (0);
	}
	return (1);
}

static int	run_shell(t_chill *shell)
{
	int		index;

	if (is_input_valid(shell))
	{
		index = 0;
		shell->tree = make_tree(shell->input, &index);
		if (!shell->tree)
			return (1);
		if (exec_tree(shell->tree, shell) != 0)
			return (ft_btree_free_all(&shell->tree), 1);
		ft_btree_free_all(&shell->tree);
	}
	return (0);
}

/*
 *
 *			PLEASE TO SYNTAX ERROR CHECKING BEFORE MAKE TREE
 * UPDATE THE ERROR CODE
 * SO SYNTAX ERROR OR OTHER NON FATAL ERROR DONT EXIT SHELL
 * */
int	main(int ac, char **av, char **env)
{
	t_chill	*shell;

	(void) ac;
	(void) av;
	shell = init_shell(env);
	g_signal = 0;
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
			if (run_shell(shell) != 0)
				return (exit_shell(shell, 1));
		}
		else
		{
			printf("signal = %d\n", g_signal);
			shell->exit_status = g_signal;
		}
		free(shell->input);
	}
	return (exit_shell(shell, 0));
}
