/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:54:35 by madlab            #+#    #+#             */
/*   Updated: 2024/05/17 03:36:15 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_token_list(t_token_list **elem)
{
	t_token_list	*tmp_elem;

	if (!(*elem))
		return ;
	while ((*elem)->prev)
		*elem = (*elem)->prev;
	while (*elem)
	{
		tmp_elem = (*elem)->next;
		free((*elem)->token);
		(*elem)->token = NULL;
		free((*elem));
		(*elem) = NULL;
		(*elem) = tmp_elem;
	}
	*elem = NULL;
}

t_token_list	*add_token(t_token_list *last_token
		, t_token_list *new_token)
{
	if (!last_token)
		return (new_token);
	if (!new_token)
		return (last_token);
	last_token->next = new_token;
	new_token->prev = last_token;
	return (new_token);
}

t_token_list *get_token_list_head(t_token_list *token_list)
{
	if (!token_list)
		return (NULL);
	while (token_list->prev)
		token_list = token_list->prev;
	return (token_list);
}
