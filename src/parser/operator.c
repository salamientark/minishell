/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 02:32:42 by madlab            #+#    #+#             */
/*   Updated: 2024/05/16 17:57:13 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
 * Return char/word type (operator | word)
 * Operator list :
 *  CONTROL OPERATOR :
 *   (
 *   )
 *   ||
 *   &&
 *   |
 *  REDIRECTION OPERATOR
 *   >
 *   <
 *   >>
 *   <<
 *
 * */

char	get_operator(const char *s)
{
	if (*s == PIPE && *(s + 1) && *(s + 1) == PIPE)
		return (OR);
	else if (*s == PIPE)
		return (PIPE);
	else if (*s == AMPERSAND && *(s + 1) && *(s + 1) == AMPERSAND)
		return (AND);
	else if (*s == LESS_THAN && *(s + 1) && *(s + 1) == LESS_THAN)
		return (HERE_DOC);
	else if (*s == GREATER_THAN && *(s + 1) && *(s + 1) == GREATER_THAN)
		return (APPEND);
	else if (*s == LESS_THAN)
		return (LESS_THAN);
	else if (*s == GREATER_THAN)
		return (GREATER_THAN);
	return (0);
}

int	is_space_metachar(const char c)
{
	if (c == SPACE)
		return (1);
	if (c == TAB)
		return (1);
	if (c == NEWLINE)
		return (1);
	return (0);
}

int	is_metachar(const char c)
{
	if (is_space_metachar(c))
		return (1);
	if (c == AMPERSAND)
		return (1);
	if (c == PIPE)
		return (1);
	if (c == LEFT_PARENTHESIS)
		return (1);
	if (c == RIGHT_PARENTHESIS)
		return (1);
	if (c == GREATER_THAN)
		return (1);
	if (c == LESS_THAN)
		return (1);
	return (0);
}
