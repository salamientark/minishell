/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 11:38:58 by madlab            #+#    #+#             */
/*   Updated: 2024/06/05 19:15:17 by dbaladro         ###   ########.fr       */
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

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                             BINARY TREE UTILS                             */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
// ft_btree_free_all.c
void	ft_btree_free_all(t_btree **root_p);

// ft_btree_is_leaf_bonus.c
int		ft_btree_is_leaf(t_btree *node);

// ft-_btree_init_node_bonus.c
t_btree	*ft_btree_init_node(char *content);

// make_tree_bonus.c
t_btree	*make_tree(const char *input, int *index);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                            ADDED BONUS FILE                               */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
// parenthesis_strlen_bonus.c
int		parenthesis_strlen(const char *str, int ref);

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                       REWORKED MANDATORY FILE                             */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
// unclosed_delimiter_bonus.c
int		unclosed_delimiter(const char *input);

// syntax_error_bonus.c
int		syntax_error(const char *cmd, char **env);

// operator_bonus.c
int		can_be_operator(const char c);
char	get_operator(const char *s);
int		is_space_metachar(const char c);
int		is_metachar(const char c);

#endif
