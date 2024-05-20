/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 08:28:07 by madlab            #+#    #+#             */
/*   Updated: 2024/05/20 18:22:26 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	count_expand_word(const char *str)
{
	int	word_count;
	int	index;

	word_count = 1;
	index = 0;
	while (str[index])
	{
		if (str[index] == DOUBLE_QUOTE || str[index] == SINGLE_QUOTE)
			index += quoted_strlen(str, index, str[index]);
		if (str[index] == DOLLAR && str[index + 1]
			&& !is_whitespace_metachar(str[index + 1]))

		index++;
	}

}

char	*split_expand(const char *str)
{
	int		word_count;
	char	**expand_tab;

	if (!str)
		return (NULL);
	word_count = count_expand_word(str);
	
}

int	expand_token(t_token_list *token, char **env)
{
	int	str_index;
	int	expand_index;
	char	*expanded_word;

	expand_index = -1;
	str_index = 0;
	if (!token->token[str_i])
		return (0);
	while (token->token[str_i])
	{
		if (token->token[str_i] == DOLLAR && token->token[str_i + 1]
			&& !is_space_metachar(token->token[str_i]))
		expanded_word = get_value(token->token, str_i);
	}
}

int	expand(t_simple_cmd *cmd_tab, char **env)
{
	int				expand_result;
	t_token_list	*token_list;

	token_list = cmd_tab->cmd;
	while (token_list)
	{
		expand_result = expand_token(token_list);
		if (expand_result != 0)
			return (expand_result);
		token_list = token_list->next;
	}
}
