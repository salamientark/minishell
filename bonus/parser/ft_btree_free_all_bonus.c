/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_free_all_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:36:25 by madlab            #+#    #+#             */
/*   Updated: 2024/06/05 16:46:46 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser_bonus.h"

/* Free the tree and all branches also freeing the content
 * */
void	ft_btree_free_all(t_btree **root_p)
{
	if ((*root_p)->l_node)
		ft_btree_free_all(&(*root_p)->l_node);
	if ((*root_p)->r_node)
		ft_btree_free_all(&(*root_p)->r_node);
	free((*root_p)->content);
	(*root_p)->content = NULL;
	free(*root_p);
	*root_p = NULL;
}
