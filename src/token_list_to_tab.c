/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list_to_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 23:52:57 by madlab            #+#    #+#             */
/*   Updated: 2024/05/23 01:54:26 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static size_t	count_token(t_token_list *token_list)
{
	int		tab_size;

	tab_size = 0;
	while (token_list)
	{
		if (token_list->token)
			tab_size++;
		token_list = token_list->next;
	}
	return (tab_size);
}

char	**token_list_to_tab(t_token_list *token_list)
{
	char	**tab;
	size_t	tab_size;
	size_t	index;

	tab_size = count_token(token_list);
	tab = (char **)malloc(sizeof(char *) * (tab_size + 1));
	if (!tab)
		return (print_error("malloc", strerror(errno)), NULL);
	tab[tab_size] = NULL;
	index = 0;
	while (index < tab_size)
	{
		if (token_list->token)
		{
			tab[index] = token_list->token;
			token_list->token = NULL;
			index++;
		}
		token_list = token_list->next;
	}
	return (tab);
}
