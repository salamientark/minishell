/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_list_from_tab.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:31:07 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/22 17:23:39 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token_list	*ft_token_list_from_tab(char **tab)
{
	t_token_list	*final_list;
	t_token_list	*tmp_token;
	int				index;

	index = 0;
	final_list = NULL;
	while (tab[index])
	{
		tmp_token = ft_token_make_one(tab[index], T_EXPAND);
		if (!tmp_token)
			return (ft_token_free_list(&final_list), NULL);
		final_list = ft_token_add_back(final_list, tmp_token);
		index++;
	}
	final_list = ft_token_get_head(final_list);
	return (final_list);
}
