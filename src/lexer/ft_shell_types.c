/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_types.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 02:32:42 by madlab            #+#    #+#             */
/*   Updated: 2024/05/09 03:12:13 by madlab           ###   ########.fr       */
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

/*
 * Return 1 if the file is a control operator
 * CARREFUL it test only a char assuming that even if the nexr char is
 * the same control operator it will not change function goal
 *	EXEMPLE :
 *  << is a control operator but you will only test one char to know this
 *		So it means that you don't need to make a distinction between < and <<
 * NOTES :
 * maybe implementing a char *function because && is an operator and
 * it may be easier to treat & as a word instead
 * */
int	is_control_operator(const char c)
{
	if (c == PIPE)
		return (1);
	if (c == LEFT_PARENTHESIS)
		return (1);
	if (c == RIGHT_PARENTHESIS)
		return (1);
	if (c == AMPERSAND)
		return (1);
	return (0);
}

int	is_redirection_operator(const char c)
{
	if (c == LESS_THAN)
			return (1);
	if (c == GREATER_THAN)
			return (1);
	return (0);
}

int	is_operator(const char c)
{
	if (is_control_operator(c))
		return (1);
	if (is_redirection_operator(c))
		return (1);
	return (0);
}
