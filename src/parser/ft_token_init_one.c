/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_init_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:30:49 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/26 18:42:48 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	get_word_size(const char *input, int ref)
{
	int	word_size;

	word_size = 0;
	while (input[ref + word_size]
		&& is_space_metachar(input[ref + word_size]) == 0
		&& get_operator(&input[ref + word_size]) == 0)
	{
		if (input[ref + word_size] == SINGLE_QUOTE
			|| input[ref + word_size] == DOUBLE_QUOTE)
			word_size += quoted_strlen(input, ref + word_size,
					input[ref + word_size]);
		else if (input[ref + word_size] == DOLLAR)
			word_size += expand_strlen(input, ref + word_size, 0);
		else
			word_size++;
	}
	return (word_size);
}

t_token_list	*ft_token_init_one(const char *input)
{
	t_token_list	*new_token;
	int				token_size;

	new_token = (t_token_list *)malloc(sizeof(struct s_token_list));
	if (!new_token)
		return (print_error("malloc", strerror(errno)), NULL);
	if (get_operator(input) != 0)
		token_size = 1 + (input[1] && input[0] == input[1]);
	else
		token_size = get_word_size(input, 0);
	new_token->token = ft_strndup(input, token_size);
	if (!new_token->token)
		return (print_error("ft_strndup", "malloc error"), free(new_token)
			, NULL);
	new_token->size = token_size;
	new_token->type = (int)get_operator(input);
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}
