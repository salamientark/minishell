/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:42:06 by madlab            #+#    #+#             */
/*   Updated: 2024/05/15 18:43:16 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/error.h"

// MAYBE ERROR ARE NOT WRITTEN WITH PRINTF
// BUT STD_ERROR INSTEAD
void	syntax_error(const char *input, char operator)
{
	int			operator_len;
	const char	*input_cp;

	write(2, "minishell: syntax error near unexpected token \''", 46);
	operator_len = 2;
	input_cp = input;
	if (operator == PIPE || operator == AND || operator == OR)
		operator_len = 1;
	else
	{
		while (*input_cp && (*input_cp == ' ' || *input_cp == '\t'))
			input_cp++;
		if (!*input_cp || *input_cp == '\n')
			write(2, "newline", 7);
		else
			write(2, input, operator_len);
	}
	write(2, "\'", 1);
}
