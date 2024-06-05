/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:26:14 by madlab            #+#    #+#             */
/*   Updated: 2024/06/04 22:56:55 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Return the len of quoted word + 2 for quote OR
// -1 when no quote found 
int	quoted_strlen(const char *str, int ref, const char quote)
{
	int	len;
	int	var_expand_len;

	len = 1;
	while (str[ref + len] && str[ref + len] != quote)
	{
		if (str[ref + len] == DOLLAR && str[ref + len + 1]
			&& str[ref + len + 1] == LEFT_BRACE && quote == DOUBLE_QUOTE)
		{
			if (quote == DOUBLE_QUOTE)
				var_expand_len = expand_strlen(str, ref + len, 1);
			else
				var_expand_len = expand_strlen(str, ref + len, 0);
			if (var_expand_len == -1)
				return (-1);
			len += var_expand_len;
		}
		else
			len++;
	}
	if (!str[ref + len])
		return (unclosed_delimiter_error(str, ref), -1);
	return (len + 1);
}
