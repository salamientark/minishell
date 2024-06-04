/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simplify_pattern_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 01:59:23 by madlab            #+#    #+#             */
/*   Updated: 2024/06/04 16:11:46 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expander_bonus.h"

static char	*make_simplified_pattern(char *dest, t_expand *pattern, int index,
	int diff)
{
	while (pattern->word[index + diff])
	{
		if (pattern->quote[index + diff])
		{
			while (pattern->quote[index + diff + 1] != 1)
			{
				dest[index] = pattern->word[index + diff + 1];
				index++;
			}
			diff += 2;
		}
		else if (pattern->word[index + diff] == '*' && dest[index]
				&& dest[index] == '*')
			diff++;
		else
			dest[index] = pattern->word[index + diff];
		index++;
	}
	ft_memset(dest + index, 0, diff + 1);
	return (dest);
}

char	*simplify_pattern(t_expand *pattern)
{
	char	*result;

	result = (char *)malloc(pattern->size + 1);
	if (!result)
		return (print_error("malloc", strerror(errno)), NULL);
	ft_memset(result, 0, pattern->size);
	result = make_simplified_pattern(result, pattern, 0, 0);
	return (result);
}
