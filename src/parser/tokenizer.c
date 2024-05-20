/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:52:38 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/17 15:15:55 by dbaladro         ###   ########.fr       */
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
			word_size += expand_strlen(input, ref + word_size);
		else
			word_size++;
	}
	return (word_size);
}

static t_token_list	*make_token(const char *input, int ref)
{
	t_token_list	*new_token;
	int				token_size;

	new_token = (t_token_list *)malloc(sizeof(struct s_token_list));
	if (!new_token)
		return (print_error("malloc", strerror(errno)), NULL);
	if (get_operator(&input[ref]) != 0)
		token_size = 1 + (input[ref + 1] && input[ref] == input[ref + 1]);
	else
		token_size = get_word_size(input, ref);
	new_token->token = ft_strndup(input + ref, token_size);
	if (!new_token->token)
		return (print_error("ft_strndup", "malloc error"), free(new_token)
			, NULL);
	new_token->size = token_size;
	new_token->type = (int)get_operator(input + ref);
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

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
			new_token = make_token(input, index);
			if (!new_token)
				return (free_token_list(&last_token), NULL);
			last_token = add_token(last_token, new_token);
			index += last_token->size;
		}
		else
			index++;
	}
	last_token = get_token_list_head(last_token);
	return (last_token);
}
