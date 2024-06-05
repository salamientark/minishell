/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_tree_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:13:50 by dbaladro          #+#    #+#             */
/*   Updated: 2024/06/05 19:00:59 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser_bonus.h"

static void	skip_space(const char *input, int *index)
{
	while (input[*index] && is_space_metachar(input[*index]))
		*index += 1;
}

/* Perform ft_strndup and ft_strtrim freeinf the temporary element
 * */
static char	*dup_and_trim(const char *str, int size, const char *set)
{
	char	*dup_result;
	char	*trim_result;

	dup_result = ft_strndup(str, size);
	if (!dup_result)
		return (print_error("ft_strndup", "malloc error"), NULL);
	trim_result = ft_strtrim(dup_result, set);
	if (!trim_result)
		return (print_error("ft_strtrim", "malloc error"), free(dup_result),
			NULL);
	return (free(dup_result), trim_result);
}

/* make a new_node from the input starting at index
 * Updating index at the end
 * */
static t_btree	*make_new_node(const char *input, int *index)
{
	char	*content;
	char	operator;
	int		content_len;
	t_btree	*new_node;

	content_len = 0;
	while (input[*index + content_len] && input[*index + content_len] != ')')
	{
		operator = get_operator(input + *index + content_len);
		if ((operator == AND || operator == OR) && content_len == 0)
			content_len += 2;
		if (operator == AND || operator == OR)
			break ;
		content_len++;
	}
	content = dup_and_trim(input + *index, content_len, " \t\n");
	if (!content_len)
		return (print_error("malloc", strerror(errno)), NULL);
	new_node = ft_btree_init_node(content);
	if (!new_node)
		return (print_error("ft_btree_init_node", "fail"), free(content), NULL);
	*index += content_len;
	return (new_node);
}

/* return the new root after the new_node have been correctly added
 * */
static t_btree	*add_node(t_btree *root, t_btree *new_node)
{
	if (!root)
		return (new_node);
	if (ft_btree_is_leaf(new_node) && (ft_strcmp("&&", new_node->content) == 0
		|| ft_strcmp("||", new_node->content) == 0))
	{
		new_node->l_node = root;
		return (new_node);
	}
	root->r_node = new_node;
	return (root);
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

	root = NULL;
	skip_space(input, index);
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
		root = add_node(root, new_node);
	skip_space(input, index);
	}
	if (input[*index])
		*index += 1;
	return (root);
}
