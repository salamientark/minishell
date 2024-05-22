/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_insert_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:03:19 by madlab            #+#    #+#             */
/*   Updated: 2024/05/22 16:26:15 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* insert to token list to_insert just after src.
 * Everything after src will be after to insert.
 * src will point at then end of to_insert
 * SPECIAL CASE :
 * If no list to_insert RETURN src
 * If no list src return to_insert THEN src will point at the end of to_insert
 **/
t_token_list	*ft_token_insert_list(t_token_list *src, t_token_list *to_insert)
{
	t_token_list	*tmp_token;

	if (!to_insert && !src)
		return (NULL);
	if (!to_insert)
		return (src);
	if (!src)
	{
		while (to_insert->next)
			to_insert = to_insert->next;
		return (to_insert);
	}
	if (to_insert->prev)
		(to_insert->prev)->next = NULL;
	to_insert->prev = src;
	tmp_token = src->next;
	src->next = to_insert;
	while (src->next)
		src = src->next;
	src->next = tmp_token;
	if (tmp_token)
		tmp_token->prev = src;
	return (src);
}
