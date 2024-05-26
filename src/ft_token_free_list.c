/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_free_list.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:29:35 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/22 13:29:44 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	ft_token_free_list(t_token_list **elem)
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
