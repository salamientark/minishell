/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:42:06 by madlab            #+#    #+#             */
/*   Updated: 2024/05/15 21:32:40 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/error.h"

// MAYBE ERROR ARE NOT WRITTEN WITH PRINTF
// BUT STD_ERROR INSTEAD
void	syntax_error(const char *input, int ref, char operator)
{
	int			operator_len;

	write(2, "minishell: syntax error near unexpected token \''", 47);
	operator_len = 1;
	if (operator == PIPE || operator == AND || operator == OR)
	{
		operator_len += (operator == AND || operator == OR);
		write(2, input + ref, operator_len);
	}
	else
	{
		ref += 1 + (operator == HERE_DOC || operator == APPEND);
		while (input[ref] && (input[ref] == SPACE || input[ref] == TAB))
			ref++;
		if (!input[ref] || input[ref] == NEWLINE)
			write(2, "newline", 7);
		else
			write(2, input + ref, operator_len);
	}
	write(2, "\'\n", 2);
}
