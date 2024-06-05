/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:38:58 by madlab            #+#    #+#             */
/*   Updated: 2024/06/05 13:45:47 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_BONUS_H
# define PARSER_BONUS_H

# include "../../includes/parser.h"

typedef struct s_btree
{
	void			*content;
	struct s_btree	*l_node;
	struct s_btree	*r_node;

}				t_btree;

// ft_btree_free_all.c
void	ft_btree_free_all(t_btree **root_p);

// ft-_btree_init_node_bonus.c
t_btree	*ft_tree_init_node(char *content);

// parenthesis_strlen_bonus.c
int		parenthesis_strlen(const char *str, int ref);

#endif
