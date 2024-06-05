/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:27:53 by madlab            #+#    #+#             */
/*   Updated: 2024/06/05 14:23:10 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser_bonus.h"

static t_btree	*make_new_node(const char *input, int *index)
{
	char	*content;
	int		content_len;

	content_len = 0;
	while (input[*index + content_len] && input[*index + content_len] != ')')
	{
		
	}
}

/* Recusivly make a tree splitting the input into different commad group
 *  Which mean basicaly splitting by && amd ||. 
 *  '(' mean begining of sub-tree
 *  ')' mean end of sub-tree
 * */
t_btree	*make_tree(const char *input, int *index)
{
	t_btree	*root;
	t_btree	*new_node;
	int		operator;

	root = NULL;
	index = 0;
	while (input[*index] && input[*index] != RIGHT_PARENTHESIS)
	{
		if (input[*index] == LEFT_PARENTHESIS)
		{
			*index += 1;
			new_node = make_tree(input, index);
		}
		else
			new_node = make_new_node(input, index);
		if (!new_node)
			return (ft_btree_free_all(&root), NULL);
		root = 

	}
	if (input[*index])
		*index += 1;
	return (root);
}
