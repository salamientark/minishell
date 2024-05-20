/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 08:28:07 by madlab            #+#    #+#             */
/*   Updated: 2024/05/21 01:06:13 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	expand_error(const char *word)
{
	int	index;

	index = 2;
	if (word[index] && (word[index] == RIGHT_BRACE || ft_isnbr(word[index])))
		return (print_error(word, "bad substitution"), 1);
	while (word[index] && word[index] != RIGHT_BRACE)
	{
		if (word[index] == SINGLE_QUOTE || word[index] == DOUBLE_QUOTE
			|| can_be_operator(word[index] || word[index] == LEFT_PARENTHESIS
				|| word[index] == RIGHT_PARENTHESIS || word[index] == LEFT_BRACE))
			return (print_error(word, "bad substitution"), 1);
		index++;
	}
	return (0);
}

static int	get_expand_len(const char *to_expand, char **env)
{
	int	len;

	len = 0;
	while (to_expand[len] && (ft_isalnum(to_expand[len])
		|| to_expand[len] == UNDERSCORE))
		len++;
	return (len);
}

char	*expand(const char *to_expand, char **env)
{
	int		ref;
	int		expand_len;
	char	*expanded_word;

	ref = 1;
	if (to_expand[ref] && to_expand[ref] == LEFT_BRACE)
	{
		ref++;
		if (expand_error(to_expand))
			return (NULL);
		expand_len = get_expand_len(to_expand + ref);
	}
	else
		expand_len = get_expand_len(to_expand + ref);
	expanded_word = get_env_val(to_expand + ref, )
}

char	*join_expand(char **splited_expand, char **env)
{
	char	*tmp_str;
	char	*final_str;
	int		index;

	final_str = NULL;
	index = 0;
	while (splited_expand[index])
	{
		if (splited_expand[index][0] == DOLLAR)
		{
			tmp_str = expand(splited_expand[index], env);
			if (!tmp_str)
				// ERROR
			free(splited_expand[index]);
			splited_expand[index] = tmp_str;
		}
		tmp_str = final_str;
		final_str = ft_strjoin(final_str, splited_expand[index]);
		free(tmp_str);
		index++;
	}
	return (final_str);
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
