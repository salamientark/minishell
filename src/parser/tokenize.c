/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:52:38 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/26 18:37:20 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token_list	*tokenize(const char *input)
{
	int				index;
	t_token_list	*last_token;
	t_token_list	*new_token;

	index = 0;
	last_token = NULL;
	while (input[index])
	{
		if (!is_space_metachar(input[index]))
		{
			new_token = ft_token_init_one(input + index);
			if (!new_token)
				return (ft_token_free_list(&last_token), NULL);
			last_token = ft_token_add_back(last_token, new_token);
			index += last_token->size;
		}
		else
			index++;
	}
	last_token = ft_token_get_head(last_token);
	return (last_token);
}
