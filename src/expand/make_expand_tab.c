/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_expand_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 14:14:23 by madlab            #+#    #+#             */
/*   Updated: 2024/05/29 18:49:28 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

// Properly free the t_expand_type on error
static void	free_all(t_expand ***expand_p, int last_pos)
{
	int	index;

	index = 0;
	while (index < last_pos)
	{
		free((*expand_p)[index]->quote);
		(*expand_p)[index]->quote = NULL;
		free((*expand_p)[index]);
		(*expand_p)[index] = NULL;
		index++;
	}
	free(*expand_p);
	*expand_p = NULL;
}

// Create a t_expand element
static	t_expand	*make_expand_elem(char *str)
{
	t_expand	*expand_elem;
	int			index;

	expand_elem = (t_expand *)malloc(sizeof(struct s_expand));
	if (!expand_elem)
		return (print_error("malloc", strerror(errno)), NULL);
	expand_elem->quote = (int *)malloc(sizeof(int) * ft_strlen(str));
	if (!expand_elem->quote)
		return (print_error("malloc", strerror(errno)), free(expand_elem),
			NULL);
	index = 0;
	memset(expand_elem->quote, 0, ft_strlen(str) * sizeof(int));
	while (str[index])
	{
		if (str[index] == DOUBLE_QUOTE || str[index] == SINGLE_QUOTE)
		{
			expand_elem->quote[index] = 1;
			index += quoted_strlen(str, index, str[index]);
			expand_elem->quote[index - 1] = 1;
		}
		else
			index++;
	}
	expand_elem->word = str;
	return (expand_elem);
}

// Create a t_expand array filling the type part using the following rule :
// If the quote should be remove at the end of expansion -> Set 1
// Else -> Set 0
// We will fill every expand->quote value resulting from expansion with 0
t_expand	**make_expand_tab(char **tab)
{
	t_expand	**expand_tab;
	int			index;

	expand_tab = (t_expand **)malloc(sizeof(t_expand *)
			* (ft_tab_size(tab) + 1));
	if (!expand_tab)
		return (print_error("malloc", strerror(errno)), NULL);
	index = 0;
	while (tab[index])
	{
		expand_tab[index] = make_expand_elem(tab[index]);
		if (!expand_tab[index])
			return (free_all(&expand_tab, index), NULL);
		index++;
	}
	expand_tab[index] = NULL;
	return (expand_tab);
}
