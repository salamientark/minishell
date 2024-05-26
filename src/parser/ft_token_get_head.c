/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_get_head.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:31:27 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/26 18:43:06 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token_list	*ft_token_get_head(t_token_list *token_list)
{
	t_token_list	*new_head;

	if (!token_list)
		return (NULL);
	new_head = token_list;
	while (new_head->prev)
		new_head = new_head->prev;
	return (new_head);
}
