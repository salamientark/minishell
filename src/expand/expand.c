/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 08:28:07 by madlab            #+#    #+#             */
/*   Updated: 2024/05/20 22:31:36 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	get_expand_len(const char *str, int ref)
{
	int	len;

	len = 1;
	if (ft_isnbr(str[len]))
		return (len + 1);
	if (str[ref + len] && str[ref + index] == LEFT_BRACE)
	{
		len++;
		while (str[ref + len] && str[ref + len] != RIGHT_BRACE)
		{
			if (str[ref + len] == SINGLE_QUOTE
				|| str[ref + len] == DOUBLE_QUOTE)
				len += quoted_strlen(str, ref + index, str[ref + index]);
			else
				len++;
		}
		return (len);
	}
	while (str[ref + len]
		&& (ft_isalnum(str[ref + len]) || str[ref + index] == UNDERSCORE))i
		len++;
	return (len);
}

static int	count_expand_word(const char *str)
{
	int	word_count;
	int	index;
	int	in_double_quote;

	word_count = 1;
	index = 0;
	while (str[index])
	{
		if (str[index] == DOUBLE_QUOTE)
			in_double_quote = 1 ^ in_double_quote;
		else if (str[index] == SINGLE_QUOTE && !in_double_quote)
			index += quoted_strlen(str, index, str[index]);
		else if (str[index] == DOLLAR && str[index + 1]
			&& !is_whitespace_metachar(str[index + 1]))
		{
			word_count++;
			index += get_expand_len(str, index);
		}
		else
			index++;
	}
	return (word_count);
}

static char	*extract_word(const char **str)
{
	int	word_size;

	if (!*str)
		return (NULL);
	if (**str == DOLLAR && *(str + 1) && !ft_isnbr(*(str + 1)))
		word_size = get_expand_len(*str, ref);
	else
	{
		word_size = 0;
		while (**str && !(**str == DOLLAR && *(str + 1) && !ft_isnbr(*(str + 1))))
		{
			if (**str == SINGLE_QUOTE)
				*str += quoted_strlen(*str, 0, **str);
			else
				*str++;
		}
	}
}

char	*split_expand(const char *str, const char **path)
{
	int		word_count;
	int		index;
	char	**expand_tab;

	if (!str)
			return (NULL);
	word_count = count_expand_word(str);
	expand_tab = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!expand_tab)
		return (print_error("malloc", strerror(errno)), NULL);
	index = 0;
	while (str[index] = 0)
	{
		expand_tab[index] = extract_word(&str);
		if (!expand_tab[index])
			// ERROR -> FREE_ALL
		index++;
	}
	return (expand_tab);
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
			&& !is_space_metachar(token->token[str_i])
				&& !ft_isnbr(tokken->token[str_i]))
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
