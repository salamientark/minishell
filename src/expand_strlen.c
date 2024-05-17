/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_strlen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 19:22:17 by madlab            #+#    #+#             */
/*   Updated: 2024/05/17 01:47:29 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// Return the len of braced expand len + 2 for brace 
// OR -1 on error
static int	brace_expand_len(const char *input, int ref)
{
	int	len;
	int	delimited_word_len;

	len = 1;
	while (input[ref + len] && input[ref + len] != RIGHT_BRACE)
	{
		delimited_word_len = 1;
		if (input[ref + len] == SINGLE_QUOTE
			|| input[ref + len] == DOUBLE_QUOTE)
			delimited_word_len = quoted_strlen(input,
					ref + len, input[ref + len]);
		if (delimited_word_len == -1)
			return (-1);
		len += delimited_word_len;
	}
	if (!input[ref + len])
		return (unclosed_delimiter_error(input, ref + 1), -1);
	return (len);
}

// OBVIOUS
int	expand_strlen(const char *input, int ref)
{
	int	len;

	len = 1;
	if (!input[ref + len])
		return (len);
	if (input[ref + len] == LEFT_BRACE)
	{
		len = brace_expand_len(input, ref);
		if (len == -1)
			return (len);
	}
	else
	{
		while (ft_isalnum(input[ref + len]))
			len++;
	}
	return (len);
}
