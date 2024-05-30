/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_word_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:22:34 by madlab            #+#    #+#             */
/*   Updated: 2024/05/30 19:25:32 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

/* Properly free a single t_expand element
 */
static void	free_expand_elem(t_expand **elem_p)
{
	free((*elem_p)->word);
	(*elem_p)->word = NULL;
	free((*elem_p)->quote);
	(*elem_p)->quote = NULL;
	free(*elem_p);
	*elem_p = NULL;
}

/* If the elem->word result is result from an UNQUOTED variable expansion,
 * and contain space/tab/newline THEN return 1
 * ELSE
 * return 0
 * */
static int	contain_word_split(t_expand *elem)
{
	int	index;

	index = 0;
	while (elem->word[index])
	{
		if (elem->quote[index] == 1)
		{
			index++;
			while (elem->word[index] && elem->quote[index] != 1)
				index++;
			index += (elem->word[index] != '\0');
		}
		else if (is_space_metachar(elem->word[index]))
			return (1);
		else
			index++;
	}
	return (0);
}

/* Alloc the final t_expand ** resulting after word_split have been performed
 * */
static t_expand	**alloc_final_tab(t_expand **expand_tab, t_expand **to_insert)
{
	size_t		final_size;
	int			index;
	t_expand	**final_expand_tab;

	index = 0;
	while (expand_tab[index])
		index++;
	final_size = index;
	index = 0;
	while (to_insert[index])
		index++;
	final_size += index;
	final_expand_tab = (t_expand **)malloc(sizeof(t_expand *) * final_size);
	if (!final_expand_tab)
		return (print_error("malloc", strerror(errno)), NULL);
	final_expand_tab[final_size - 1] = NULL;
	return (final_expand_tab);
}

/* Properly free the  expand_tab[*index_p] element
 * And insert the to_insert tab instead reallocating the final_tab accordingly 
 * */
static t_expand	**expand_replace(t_expand **expand_tab, t_expand **to_insert,
	int *index_p)
{
	int			expand_tab_index;
	int			index;
	t_expand	**final_expand;

	final_expand = alloc_final_tab(expand_tab, to_insert);
	if (!final_expand)
		return (free_expand_tab(&expand_tab), free_expand_tab(&to_insert),
			NULL);
	expand_tab_index = 0;
	while (expand_tab_index < *index_p)
	{
		final_expand[expand_tab_index] = expand_tab[expand_tab_index];
		expand_tab_index++;
	}
	free_expand_elem(&expand_tab[expand_tab_index++]);
	index = -1;
	while (to_insert[++index])
		final_expand[expand_tab_index + index - 1] = to_insert[index];
	*index_p += index;
	while (expand_tab[expand_tab_index])
	{
		final_expand[expand_tab_index + index] = expand_tab[expand_tab_index];
		expand_tab_index++;
	}
	return (free(expand_tab), free(to_insert), final_expand);
}

/* Perform word split on every element of expand_tab when needed
 * Return 0 on SUCCESS else return 0
 * */
int	perform_word_split(t_expand ***expand_tab)
{
	int			index;
	t_expand	**word_split_result;

	if (!expand_tab || !*expand_tab)
		return (0);
	index = 0;
	while ((*expand_tab)[index])
	{
		if (contain_word_split((*expand_tab)[index]))
		{
			word_split_result = word_split((*expand_tab)[index]);
			if (!word_split_result)
				return (1);
			*expand_tab = expand_replace(*expand_tab, word_split_result,
					&index);
			if (!*expand_tab)
				return (1);
		}
		else
			index++;
	}
	return (0);
}
