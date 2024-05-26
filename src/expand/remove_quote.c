/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:24:08 by madlab            #+#    #+#             */
/*   Updated: 2024/05/22 15:26:49 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*remove_quote_str(char *str, int *in_quote)
{
	int		index;
	int		token_index;
	char	*new_str;

	if (!str)
		return (0);
	new_str = (char *)malloc(ft_strlen(str) + 1);
	if (!new_str)
		return (print_error("malloc", strerror(errno)), NULL);
	index = 0;
	token_index = 0;
	while (str[index])
	{
		if (str[index] == *in_quote)
			*in_quote = 0;
		else if (*in_quote == 0 && (str[index] == DOUBLE_QUOTE
				|| str[index] == SINGLE_QUOTE))
			*in_quote = str[index];
		else
			new_str[token_index++] = str[index];
		index++;
	}
	new_str[token_index] = '\0';
	return (ft_memset(new_str + token_index, 0, token_index - index), new_str);
}

int	remove_quote(t_token_list *expansion_result)
{
	int				in_quote;
	char			*unquoted_token;
	t_token_list	*pos;

	pos = expansion_result;
	while (pos)
	{
		if (pos->type == WORD)
		{
			unquoted_token = remove_quote_str(pos->token, &in_quote);
			if (!unquoted_token)
				return (1);
			free(pos->token);
			pos->token = NULL;
			pos->token = unquoted_token;
		}
		pos = pos->next;
	}
	return (0);
}
