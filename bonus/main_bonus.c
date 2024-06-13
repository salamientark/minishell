/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:46:40 by dbaladro          #+#    #+#             */
/*   Updated: 2024/06/13 12:42:41 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

int	g_signal = 0;

/* This function is the main loop of minishell
 * The return value indicates if the shell return normally (No fatal error)
 * */
static int	run_shell(t_chill *shell)
{
	int		index;
	t_btree	*tree;

	while ("this is the best minishell")
	{
		index = 0;
		unlink_here_doc();
		shell->input = display_prompt();
		if (!shell->input)
			break ;
		if (ft_strlen(shell->input) > 0)
		{
			tree = make_tree(shell->input, &index);
			if (!tree)
				return (1);
			if (exec_tree(tree, shell) != 0)
				return (ft_btree_free_all(&tree), 1);
			ft_btree_free_all(&tree);
		}
		free(shell->input);
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
	int		exit_status;

	(void) ac;
	(void) av;
	shell = init_shell(env);
	if (!shell)
		return (1);
	exit_status = run_shell(shell);
	return (exit_shell(shell, exit_status));
}
