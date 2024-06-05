/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_is_leaf_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:14:25 by dbaladro          #+#    #+#             */
/*   Updated: 2024/06/05 17:31:50 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser_bonus.h"

int	ft_btree_is_leaf(t_btree *node)
{
	if (node->l_node == NULL && node->r_node == NULL)
		return (1);
	return (0);
}
