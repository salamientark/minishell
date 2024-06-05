/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_init_node_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:14:41 by madlab            #+#    #+#             */
/*   Updated: 2024/06/05 18:53:25 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser_bonus.h"

/* Init a tree node filling the content with content
 * if content is NULL return NULL
 * */
t_btree	*ft_btree_init_node(char *content)
{
	t_btree	*leaf;

	leaf = (t_btree *)malloc(sizeof(struct s_btree));
	if (!leaf)
		return (NULL);
	leaf->content = content;
	leaf->r_node = NULL;
	leaf->l_node = NULL;
	return (leaf);
}
