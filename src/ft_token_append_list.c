/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_append_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:31:07 by madlab            #+#    #+#             */
/*   Updated: 2024/05/22 16:37:08 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token_list	*ft_token_append_list(t_token_list *dest, t_token_list *src)
{
	if (!dest && !src)
		return (NULL);
	if (!dest)
	{
		while (src->next)
			src = src->next;
		return (src);
	}
	while (dest->next)
		dest = dest->next;
	if (!src)
		return (dest);
	dest->next = src;
	src->prev = dest;
	while (src->next)
		src = src->next;
	return (src);
}
