/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delimiter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:35:33 by madlab            #+#    #+#             */
/*   Updated: 2024/05/15 02:40:09 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_opening_delimiter(const char c)
{
	if (c == SINGLE_QUOTE)
		return (1);
	if (c == DOUBLE_QUOTE)
		return (1);
	if (c == LEFT_BRACE)
		return (1);
	if (c == LEFT_PARENTHESIS)
		return (1);
	return (0);
}

// int	is_closing_delimiter(const char limiter, const char c)
// {
// 	if ((c == SINGLE_QUOTE || c == DOUBLE_QUOTE) && limiter == c)
// 		return (1);
// 	if (c == RIGHT_BRACE && (limiter == LEFT_BRACE
// 				|| limiter == LEFT_PARENTHESIS))
// 		return (1);
// 	if ((limiter == LEFT_PARENTHESIS || limiter == LEFT_BRACE)
// 			&& limiter == LEFT_PARENTHESIS)
// 		return (1);
// 	return (0);
// }

