/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:40:31 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/09 03:30:37 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unclosed_quote(const char *input)
{
	int	index;
	int	last_quote;

	if (!input)
		return (0);
	last_quote = 0;
	index = 0;
	while (input[index])
	{
		if (input[index] == DOUBLE_QUOTE && last_quote == 0)
			last_quote = DOUBLE_QUOTE;
		else if (input[index] == DOUBLE_QUOTE && last_quote == DOUBLE_QUOTE)
			last_quote = 0;
		else if (input[index] == SINGLE_QUOTE && last_quote == 0)
			last_quote = SINGLE_QUOTE;
		else if (input[index] == SINGLE_QUOTE && last_quote == SINGLE_QUOTE)
			last_quote = 0;
		else
			continue ;
		index++;
	}
	return (last_quote != 0);
}

int	unclosed_quote_bracket(const char *input)
{
	int		index;
	int		open_brace;
	char	last_quote;

	if (!input)
		return (0);
	index = 0;
	last_quote = 0;
	open_brace = 0;
	while (input[index])
	{
		// CLOSE BRACE
		if (input[index] == RIGHT_BRACE && open_brace == 1 && last_quote == 0)
			open_brace = 0;
		// CLOSE QUOTE
		if (input[index] == last_quote)
			last_quote = 0;

		// OPEN_BRACE
		if (input[index] == DOLLAR && (index == 0 || input[index - 1]
				!= DOLLAR) && input[index + 1] && input[index + 1] == LEFT_BRACE)
			open_brace = 1;
		// OPEN BRACE
		// if (input[index] == LEFT_BRACE && open_brace == 0 && last_quote == 0)
		// 	open_brace = 1;
		// OPEN QUOTE
		if ((input[index] == DOUBLE_QUOTE || input[index] == SINGLE_QUOTE) && last_quote == 0)
			last_quote = input[index];
		// DOLLAR OPEN BRACe
		index++;
	}
	return (open_brace == 1 || last_quote != 0);
}
