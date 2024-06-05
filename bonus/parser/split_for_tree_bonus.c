/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_for_tree_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:20:11 by madlab            #+#    #+#             */
/*   Updated: 2024/06/05 13:26:16 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser_bonus.h"

static int	count_word(const char *input)
{
	int		word_count;
	char	operator;
	int		index;

	word_count = 0;
	index = 0;
	while (input[index])
	{
		if (input[index] == SINGLE_QUOTE || input[index] == DOUBLE_QUOTE)
			index += quoted_strlen(input, index, input[index]);
		else
		{
			operator = get_operator(input + index);
			if (operator == AND || operator == OR || operator == LEFT_PARENTHESIS
				|| operator == RIGHT_PARENTHESIS)
			{
				word_count += 1;
				index += 1 + (operator == AND || operator == OR);
			}
			index += 1;
		}
	}
	return (word_count);
}


char	**split_for_tree(const char *input)
{
	int	word_count;

	word_count = count_word(input);

}
