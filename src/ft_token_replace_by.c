/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_replace_by.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:27:33 by madlab            #+#    #+#             */
/*   Updated: 2024/05/22 15:55:42 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token_list	*ft_token_replace_by(t_token_list **src, t_token_list *replace_by)
{
	t_token_list	*replace_by_head;

	if ((!src || !(*src)) && !replace_by)
		return (NULL);
	if (!replace_by)
		return (*src);
	replace_by_head = replace_by;
	while (replace_by->next)
		replace_by = replace_by->next;
	if (!src || !(*src))
		return (replace_by);
	if ((*src)->next)
		replace_by->next = (*src)->next;
	if ((*src)->next)
		((*src)->next)->prev = replace_by;
	if ((*src)->prev)
	{
		replace_by_head->prev = (*src)->prev;
		((*src)->prev)->next = replace_by_head;
	}
	free((*src)->token);
	free(*src);
	*src = replace_by;
	return (*src);
}
