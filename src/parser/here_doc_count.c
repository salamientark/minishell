/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 20:00:29 by madlab            #+#    #+#             */
/*   Updated: 2024/06/03 20:07:30 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	heredoc_count(const char *input)
{
	int	index;
	int	operator;
	int	here_doc_count;

	index = 0;
	here_doc_count = 0;
	while (input[index])
	{
		operator = 0;
		operator = get_operator(input + index);
		if (operator == HERE_DOC
			&& is_followed_by_word(input + index, operator))
		{
			here_doc_count++;
			index++;
		}
		index++;
	}
	return (here_doc_count);
}
