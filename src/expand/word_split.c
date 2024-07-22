/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 16:37:54 by madlab            #+#    #+#             */
/*   Updated: 2024/07/18 09:25:58 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

// Properly free the created word tab on error
static void	free_all(t_expand ***word_tab, size_t last_word)
{
	size_t	index;

	index = 0;
	while (index < last_word)
	{
		free((*word_tab)[index]->word);
		(*word_tab)[index]->word = NULL;
		free((*word_tab)[index]->quote);
		(*word_tab)[index]->quote = NULL;
		free((*word_tab)[index]);
		(*word_tab)[index] = NULL;
		index++;
	}
	free(*word_tab);
	*word_tab = NULL;
}

// Count the nbr of word after word split
static size_t	count_word(t_expand *elem)
{
	size_t	word_count;
	size_t	index;
	int		new_word;

	word_count = 0;
	index = 0;
	new_word = 1;
	while (elem->word[index])
	{
		if (elem->quote[index] == 1)
		{
			index++;
			while (elem->word[index] && elem->quote[index] != 1)
				index++;
		}
		else if (is_space_metachar(elem->word[index]))
			new_word = 1;
		else
		{
			word_count += (new_word == 1);
			new_word = 0;
		}
		index++;
	}
	return (word_count);
}

/* Create a t_expand element duplicating the 'word' and 'quote' from 'elem'
 * Starting from 'ref', it will duplicate 'size' element 
 * */
static t_expand	*expand_ndup(t_expand *elem, size_t size, size_t ref)
{
	t_expand	*new_elem;
	size_t		index;

	new_elem = (t_expand *)malloc(sizeof(struct s_expand));
	if (!new_elem)
		return (print_error("malloc", strerror(errno)), NULL);
	new_elem->word = ft_strndup(elem->word + ref, size);
	if (!new_elem->word)
		return (print_error("malloc", strerror(errno)), free(new_elem), NULL);
	new_elem->quote = (int *)malloc(sizeof(int) * size);
	if (!new_elem->quote)
		return (print_error("malloc", strerror(errno)), free(new_elem->word),
			free(new_elem), NULL);
	index = 0;
	while (elem->word[ref + index] && index < size)
	{
		new_elem->quote[index] = elem->quote[ref + index];
		index++;
	}
	new_elem->size = size;
	return (new_elem);
}

/* Extract a new t_expand element from 'elem' starting at 'word_index' position
 * It will then update the 'word_index' value to add the new_elem->word len
 * */
static t_expand	*extract_word(t_expand *elem, int *word_index)
{
	int			size;
	t_expand	*new_elem;

	size = 0;
	while (elem->word[*word_index]
		&& is_space_metachar(elem->word[*word_index]))
		*word_index += 1;
	while (elem->word[*word_index + size]
		&& !is_space_metachar(elem->word[*word_index + size]))
	{
		if (elem->quote[*word_index + size] == 1)
		{
			size++;
			while (elem->quote[*word_index + size] != 1)
				size++;
			size++;
		}
		else
			size++;
	}
	new_elem = expand_ndup(elem, size, *word_index);
	if (!new_elem)
		return (NULL);
	*word_index += ft_strlen(new_elem->word);
	return (new_elem);
}

/* Split a t_expand element to an array of t_expand
 * following the bash word_split rule
 * */
t_expand	**word_split(t_expand *elem)
{
	t_expand	**word_tab;
	size_t		tab_size;
	size_t		tab_index;
	int			word_index;

	tab_size = count_word(elem);
	word_tab = (t_expand **)malloc(sizeof(t_expand *) * (tab_size + 1));
	if (!word_tab)
		return (print_error("malloc", strerror(errno)), NULL);
	tab_index = 0;
	word_index = 0;
	while (tab_index < tab_size)
	{
		word_tab[tab_index] = extract_word(elem, &word_index);
		if (!word_tab[tab_index])
			return (free_all(&word_tab, tab_index), NULL);
		tab_index++;
	}
	word_tab[tab_index] = NULL;
	return (word_tab);
}
