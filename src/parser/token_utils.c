/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 19:54:35 by madlab            #+#    #+#             */
/*   Updated: 2024/05/17 14:45:05 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_token_list(t_token_list **elem)
{
	t_token_list	*tmp_elem;

	if (!elem || !(*elem))
		return ;
	while ((*elem)->prev)
		*elem = (*elem)->prev;
	while (*elem)
	{
		tmp_elem = (*elem)->next;
		if ((*elem)->token)
		{
			free((*elem)->token);
			(*elem)->token = NULL;
		}
		free((*elem));
		(*elem) = NULL;
		(*elem) = tmp_elem;
	}
	*elem = NULL;
}

t_token_list	*add_token(t_token_list *last_token
		, t_token_list *new_token)
{
	if (!new_token)
		return (last_token);
	if (!last_token)
	{
		new_token->prev = NULL;
		return (new_token);
	}
	last_token->next = new_token;
	new_token->prev = last_token;
	new_token->next = NULL;
	return (new_token);
}

t_token_list	*get_token_list_head(t_token_list *token_list)
{
	t_token_list	*new_head;

	if (!token_list)
		return (NULL);
	new_head = token_list;
	while (new_head->prev)
		new_head = new_head->prev;
	return (new_head);
}
