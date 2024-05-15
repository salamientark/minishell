/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delimiter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:35:33 by madlab            #+#    #+#             */
/*   Updated: 2024/05/15 14:13:23 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_opening_delimiter(const char *str)
{
	 if (*str == LEFT_PARENTHESIS)
		 return (1);
	 if (*str == LEFT_BRACE && (!*(str + 1)
			|| (*(str + 1) && (*(str + 1) == SPACE
				|| *(str + 1) == TAB))))
		return (1);
	return (0);
}

int	is_closing_delimiter(const char c, const char delimiter)
{
	if (delimiter == LEFT_PARENTHESIS && c == RIGHT_PARENTHESIS)
		return (1);
	if (delimiter == LEFT_BRACE && c == RIGHT_BRACE)
		return (1);
	return (0);
}

int	is_operator(const char *str)
{
	if (*str == PIPE)
		return (1);
	if (*str == AMPERSAND && *(str + 1) && *(str + 1) == AMPERSAND)
		return (1);
	if (*str == LEFT_PARENTHESIS)
		return (1);
	if (*str == LEFT_BRACE && *(str + 1)
			&& (*(str + 1) == SPACE || *(str + 1) == TAB))
		return (1);
	return (0);
}
