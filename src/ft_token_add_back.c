/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_add_back.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:30:25 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/22 13:30:32 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token_list	*ft_token_add_back(t_token_list *last_token
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