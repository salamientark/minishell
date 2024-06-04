/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify_pattern_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:59:23 by madlab            #+#    #+#             */
/*   Updated: 2024/06/04 01:59:54 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expand_bonus.h"

static make_simplified_pattern(char *dest, t_expand *pattern, int index,
	int diff)
{
	while (pattern->word[index + diff])
	{
		if (pattern->quote[index + diff])
		{
			while (pattern->quote[index + diff + 1] != 1)
			{
				dest[index] = patern->word[index + diff + 1];
				index++;
			}
			diff += 2;
		}
		else if (pattern->word[index + diff] == '*' && dest[index] == '*')
			diff++;
		else
			dest[index] = patter->word[index + diff];
		index++;
	}
	memset(dest + index, 0, diff);
	return (dest);
}

char	*simplify_pattern(t_expand *pattern)
{
	char	*result;

	result = (char *)malloc(pattern->size + 1);
	if (!result)
		return (print_error("malloc", strerro(errno)), NULL);
	result = make_simplified_pattern(result, pattern, 0, 0);
	return (result);
}
