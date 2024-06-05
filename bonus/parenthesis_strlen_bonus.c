/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis_strlen_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:57:30 by madlab            #+#    #+#             */
/*   Updated: 2024/06/05 11:41:05 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser_bonus.h"

static int	get_tmp_len(const char *str, int ref)
{
	int	tmp_len;

	if (str[ref] == SINGLE_QUOTE || str[ref] == DOUBLE_QUOTE)
	{
		tmp_len = quoted_strlen(str, ref, str[ref]);
		if (tmp_len == -1)
			return (unclosed_delimiter_error(str, ref), -1);
	}
	else if (str[ref] == LEFT_PARENTHESIS)
	{
		tmp_len = parenthesis_strlen(str, ref);
		if (tmp_len == -1)
			return (-1);
	}
	else if (str[ref] == DOLLAR && str[ref + 1]
		&& str[ref + 1] == LEFT_BRACE)
	{
		tmp_len = expand_strlen(str, ref, 0);
		if (tmp_len == -1)
			return (-1);
	}
	else
		tmp_len = 1;
	return (tmp_len);
}

/* return parenthesis strlen
 * */
int	parenthesis_strlen(const char *str, int ref)
{
	int	len;
	int	tmp_len;

	len = 1;
	while (str[ref + len] && str[ref + len] != RIGHT_PARENTHESIS)
	{
		tmp_len = get_tmp_len(str, ref + len);
		if (tmp_len == -1)
			return (-1);
		len += tmp_len;
	}
	if (!str[ref + len])
		return (unclosed_delimiter_error(str, ref), -1);
	return (len + 1);
	return (0);
}
