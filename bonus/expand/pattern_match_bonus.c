/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pattern_match_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:38:28 by madlab            #+#    #+#             */
/*   Updated: 2024/06/04 13:30:18 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander_bonus.c"

int	get_subpattern_len(const char *pattern, int index)
{
	int	index_cp;

	index_cp = 0;
	while (pattern[index_cp] && pattern[index_cp] != '*')
		index_cp++;
	return (index_cp - index);
}

int	pattern_match(const char *pattern, const char *word)
{
	int	pattern_index;
	int	word_index;
	int	sub_pattern_len;
	int	preceeded_by_wildcard;


	pattern_index = 0;
	word_index = 0;
	sub_pattern_len = 0;
	preceeded_by_wildcard = 0;
	while (pattern[pattern_index] && word[word_index])
	{
		if (pattern[pattern_index] == '*')
			preceeded_by_wildcard = 1;
		else if (!preceeded_by_wildcard )

	}

}
