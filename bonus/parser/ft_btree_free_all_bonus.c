/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_free_all_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:36:25 by madlab            #+#    #+#             */
/*   Updated: 2024/06/13 12:27:07 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser_bonus.h"

/* Free the tree and all branches also freeing the content
 * */
void	ft_btree_free_all(t_btree **root_p)
{
	if (!root_p || !(*root_p))
		return ;
	if ((*root_p)->l_node != NULL)
		ft_btree_free_all(&((*root_p)->l_node));
	if ((*root_p)->r_node != NULL)
		ft_btree_free_all(&((*root_p)->r_node));
	if ((*root_p)->content != NULL)
		free((*root_p)->content);
	(*root_p)->content = NULL;
	free(*root_p);
	*root_p = NULL;
}
