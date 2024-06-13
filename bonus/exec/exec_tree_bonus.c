/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:31:00 by madlab            #+#    #+#             */
/*   Updated: 2024/06/13 12:36:14 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell_bonus.h"

/* Execute the binary tree containing command part 
 * Carreful doesn't check for errors
 * */
// void	exec_tree_void(t_btree *tree, t_chill *shell)
// {
// 	if (tree->l_node)
// 		exec_tree_void(tree->l_node, shell);
// 	execution_cmd(shell);
// 	if ((ft_strcmp("||", tree->content) == 0 && shell->exit_status != 0)
// 			|| (ft_strcmp("&&", tree->content) == 0 && shell->exit_status == 0))
// 		exec_tree_void(tree->r_node, shell);
// }

/* Execute the tree resulting for '||' '&&' splitting
 * @param t_btree *tree
 * @return 1 on error else 0
 * */
int	exec_tree(t_btree *tree, t_chill *shell)
{
	int	error_status;

	error_status = 0;
	if (!tree)
		return (0);
	if (ft_btree_is_leaf(tree))
	{
		shell->cmd_tab = parse_input(tree->content, shell);
		if (!shell->cmd_tab)
			return (1);
		execution_cmd(shell);
		free_cmd_tab(&shell->cmd_tab);
	}
	if (tree->l_node)
		error_status = exec_tree(tree->l_node, shell);
	if (error_status == 1)
		return (1);
	if ((ft_strcmp("||", tree->content) == 0 && shell->exit_status != 0)
		|| (ft_strcmp("&&", tree->content) == 0 && shell->exit_status == 0))
		error_status = exec_tree(tree->r_node, shell);
	if (error_status == 1)
		return (1);
	return (0);
}
