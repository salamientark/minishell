/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 00:41:39 by madlab            #+#    #+#             */
/*   Updated: 2024/05/23 06:06:49 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_all(char ***word_tab, size_t last_word)
{
	size_t	index;

	index = 0;
	while (index < last_word)
	{
		if ((*word_tab)[index])
		{
			free((*word_tab)[index]);
			(*word_tab)[index] = NULL;
		}
		index++;
	}
	free(*word_tab);
	*word_tab = NULL;
}

static size_t	count_word(const char *word)
{
	size_t	word_count;
	size_t	index;
	int		new_word;

	word_count = 0;
	index = 0;
	new_word = 1;
	while (word[index])
	{
		if (word[index] == DOUBLE_QUOTE || word[index] == SINGLE_QUOTE)
			index += quoted_strlen(word, index, word[index]);
		else if (word[index] != SPACE && word[index] != TAB
			&& word[index] != NEWLINE)
		{
			if (new_word == 1)
				word_count++;
			new_word = 0;
		}
		else
			new_word = 1;
		index++;
	}
	return (word_count);
}

static char	*extract_word(const char **str)
{
	int		size;
	int		index;
	char	*word;

	size = 0;
	while (**str && is_space_metachar(**str))
		(*str)++;
	while ((*str)[size] && !is_space_metachar((*str)[size]))
	{
		if ((*str)[size] == SINGLE_QUOTE || (*str)[size] == DOUBLE_QUOTE)
			size += quoted_strlen(*str, size, (*str)[size]);
		else
			size++;
	}
	word = (char *)malloc(size + 1);
	if (!word)
		return (print_error("malloc", strerror(errno)), NULL);
	index = -1;
	while (++index < size)
		word[index] = (*str)[index];
	word[index] = '\0';
	(*str) += size;
	return (word);
}

char	**word_split(const char *word)
{
	char	**word_tab;
	size_t	tab_size;
	size_t	index;

	tab_size = count_word(word);
	word_tab = (char **)malloc(sizeof(char *) * (tab_size + 1));
	if (!word_tab)
		return (print_error("malloc", strerror(errno)), NULL);
	index = 0;
	while (index < tab_size)
	{
		word_tab[index] = extract_word(&word);
		if (!word_tab[index])
			return (free_all(&word_tab, index), NULL);
		index++;
	}
	word_tab[index] = NULL;
	return (word_tab);
}
