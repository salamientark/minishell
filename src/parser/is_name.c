/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_name.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:23:44 by madlab            #+#    #+#             */
/*   Updated: 2024/06/27 20:28:55 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Check if the word is a valid name according to bash standard
 * (Contain only letters, numbers and underscores AND dont start with a number)
 * return 1 if word is a valid name
 * else return 0
 * */
int	is_name(char *word)
{
	int	index;

	if (!word || word[0] == '\0')
		return (0);
	if (!(ft_isalpha(word[0]) || word[0] == UNDERSCORE))
		return (0);
	index = 1;
	while (word[index])
	{
		if (!(ft_isalnum(word[index]) || word[index] == UNDERSCORE))
			return (1);
		index++;
	}
	return (1);
}
