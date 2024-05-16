/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:52:38 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/16 19:05:22 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parser.h"

t_list	*tokenize_input(const char *input)
{
	int		index;
	t_list	*head;
	t_list	*last;
	t_list	*new_token;

	index = 0;
	head = NULL
	while (input[index])
	{
		if (is_space_metachar(input[index]))
			index++;
		else if(is_metachar(input[index]))
		{
			new_token = extract_token(input, index);
			if (!new_token)
				// ERROR
			head = ft_lstadd_back(head, new_token);
		}
	}
}
