/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_delimiter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:40:31 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/15 18:25:50 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Unclosed_delimiter will check for unclosed delimiter and report error if
 * found one
 * A delimiter is a SINGLE_QUOTE, DOUBLE_QUOTE or DOLLAR_BRACE_EXPAND (${...}) 
 * */

#include "../../includes/minishell.h"

// ERROR MSG
static void	unclosed_delimiter_error(const char *str, int ref)
{
	write(2, "minishell: unclosed \'", 21);
	write(2, (str + ref), 1);
	write(2, "\' at col ", 9);
	ft_putnbr_fd(ref, 2);
	write(2, "\n", 1);
}

// Return the len of quoted word + 2 for quote OR
// -1 when no quote found 
static int	quoted_strlen(const char *str, int ref, const char quote)
{
	int	len;

	len = 1;
	while (str[ref + len] && str[ref + len] != quote)
		len++;
	if (!str[ref + len])
		return (unclosed_delimiter_error(str, ref), -1);
	return (len + 1);
}

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
		return (unclosed_delimiter_error(input, ref), -1);
	return (len);
}

// OBVIOUS
static int	expand_strlen(const char *input, int ref)
{
	int	len;

	ref++;
	if (!input[ref])
		return (ref);
	len = 0;
	if (input[ref + len] == LEFT_BRACE)
	{
		len = brace_expand_len(input, ref);
		if (len == -1)
			return (len);
		return (len + ref);
	}
	else
		while (ft_isalnum(input[ref + len]))
			len++;
	return (len);
}

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
			delimited_word_len = expand_strlen(input, index);
		if (delimited_word_len == -1)
			return (1);
		index += delimited_word_len;
	}
	return (0);
}
