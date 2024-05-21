/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_delimiter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:40:31 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/21 19:16:47 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Unclosed_delimiter will check for unclosed delimiter and report error if
 * found one
 * A delimiter is a SINGLE_QUOTE, DOUBLE_QUOTE or DOLLAR_BRACE_EXPAND (${...}) 
 * */

#include "minishell.h"

// Check unclosed quote or dollqr_bqrce_expqnd
int	unclosed_delimiter(const char *input)
{
	int	index;
	int	delimited_word_len;

	if (!input)
		return (0);
	index = 0;
	delimited_word_len = 0;
	while (input[index])
	{
		delimited_word_len = 1;
		if (input[index] == SINGLE_QUOTE || input[index] == DOUBLE_QUOTE)
			delimited_word_len = quoted_strlen(input, index, input[index]);
		if (input[index] == DOLLAR)
			delimited_word_len = expand_strlen(input, index, 0);
		if (delimited_word_len == -1)
			return (1);
		index += delimited_word_len;
	}
	return (0);
}
