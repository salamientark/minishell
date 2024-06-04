/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_match_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:38:28 by madlab            #+#    #+#             */
/*   Updated: 2024/06/04 17:07:12 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander_bonus.h"

static int	subpattern_len(const char *pattern, int index)
{
	int	index_cp;

	index_cp = index;
	if (pattern[index] == '*')
		return (0);
	while (pattern[index_cp] && pattern[index_cp] != '*')
		index_cp++;
	return (index_cp - index);
}

static int	begin_the_same(const char *pattern, const char *word)
{
	int	index;

	index = 0;
	while (pattern[index] && pattern[index] != '*' && word[index])
	{
		if (pattern[index] != word[index])
			return (0);
		index++;
	}
	if (!pattern[index] || pattern[index] == '*')
		return (index);
	return (0);
}

static int	end_the_same(const char *pattern, const char *word)
{
	size_t	pattern_len;
	size_t	word_len;
	size_t	index;

	pattern_len = ft_strlen(pattern);
	word_len = ft_strlen(word);
	index = 0;
	while (pattern_len - index >= 0 && word_len - index >= 0
		&& pattern[pattern_len - index] != '*')
	{
		if (pattern[pattern_len - index] != word[word_len - index])
			return (0);
		index++;
	}
	if (index == pattern_len || pattern[pattern_len - index] == '*')
		return (1);
	return (0);
}

static int	match_subpattern(const char *pattern, const char *word,
	int *pattern_index, int *word_index)
{
	int	subpattern_size;

	subpattern_size = subpattern_len(pattern, *pattern_index);
	if (!pattern[*pattern_index + subpattern_size])
		return (end_the_same(pattern, word));
	while (word[*word_index] && ft_strncmp(pattern + *pattern_index,
			word + *word_index, subpattern_size) != 0)
		*word_index += 1;
	if (!word[*word_index])
		return (0);
	*pattern_index += subpattern_size;
	return (1);
}

int	pattern_match(const char *pattern, const char *word)
{
	int	word_index;
	int	pattern_index;

	word_index = 0;
	pattern_index = 0;
	if (pattern[0] != '*' && !begin_the_same(pattern, word))
		return (0);
	while (word[word_index])
	{
		if (!pattern[pattern_index])
			return (1);
		if (pattern[pattern_index] == '*')
			pattern_index++;
		else
		{
			if (!match_subpattern(pattern, word, &pattern_index, &word_index))
				return (0);
		}
	}
	return (pattern[pattern_index] != '\0');
}
