/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_cmd_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 21:57:38 by madlab            #+#    #+#             */
/*   Updated: 2024/05/22 17:31:06 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	contain_expand(const char *str)
{
	int	index;
	int	in_double_quote;

	index = 0;
	if (!str || !str[index])
		return (0);
	in_double_quote = 0;
	while (str[index])
	{
		if (str[index] == DOUBLE_QUOTE)
		{
			in_double_quote = 1 ^ in_double_quote;
			index++;
		}
		else if (str[index] == SINGLE_QUOTE && in_double_quote == 0)
			index += quoted_strlen(str, index, str[index]);
		else if (is_expand(str + index))
			return (1);
		else
			index++;
	}
	return (0);
}

static int	is_word_quoted(char *word, int in_double_quote)
{
	int	index;

	index = 0;
	while (word[index])
	{
		if (word[index] == SINGLE_QUOTE && !in_double_quote)
			index += quoted_strlen(word, index, word[index]);
		else if (word[index] == DOUBLE_QUOTE)
		{
			in_double_quote = 1 ^ in_double_quote;
			index++;
		}
		else
			index++;
	}
	return (in_double_quote);
}

static	int	contain_space_metachar(const char *s)
{
	int	index;

	if (!s)
		return (0);
	index = 0;
	while (s[index])
	{
		if (is_space_metachar(s[index]))
			return (1);
		index++;
	}
	return (0);
}

static t_token_list	*cmd_var_expand(char *token, int in_double_quote,
	char **env)
{
	char			*var_expand_result;
	char			**expanded_cmd;
	t_token_list	*tokenized_expand;

	var_expand_result = var_expand(token, env);
	if (!var_expand_result)
		return (NULL);
	if (!in_double_quote && var_expand_result[0] && contain_space_metachar(var_expand_result))
	{
		expanded_cmd = ft_split_str(var_expand_result, " \t\n");
		print_char_tab(expanded_cmd);
		if (!expanded_cmd)
			return (print_error("malloc", strerror(errno)), NULL);
		free(var_expand_result);
	}
	else
	{
		expanded_cmd = (char **)malloc(sizeof(char *) * 2);
		if (!expanded_cmd)
			return (print_error("malloc", strerror(errno)), NULL);
		expanded_cmd[0] = var_expand_result;
		expanded_cmd[1] = NULL;
	}
	tokenized_expand = ft_token_list_from_tab(expanded_cmd);
	if (!tokenized_expand)
		return (free(expanded_cmd), NULL);
	return (free(expanded_cmd), tokenized_expand);
}

/* Make a token_list form the actual word
 * if the word contain expansion it will make a token list according to
 * the PARAMETER EXPANSION rule
 * */
static t_token_list	*expand_cmd_token(const char *word, char **env)
{
	char			**splited_token;
	t_token_list	*tmp_expand;
	t_token_list	*expand_result;
	int				index;
	int				in_double_quote;

	splited_token = split_expand(word);

	printf("\n\n\n");
	print_char_tab(splited_token);

	if (!splited_token)
		return (NULL);
	index = 0;
	in_double_quote = 0;
	expand_result = NULL;
	while (splited_token[index])
	{
		in_double_quote = is_word_quoted(splited_token[index], in_double_quote);
		if (is_expand(splited_token[index]))
		{
			tmp_expand = cmd_var_expand(splited_token[index], in_double_quote, env);
			if (!tmp_expand)
				return (ft_free_char_tab(&splited_token), NULL);
			expand_result = ft_token_insert_list(expand_result, tmp_expand);
		}
		else
		{
			tmp_expand = ft_token_init_one(splited_token[index]);
			if (!tmp_expand)
				return (ft_free_char_tab(&splited_token), NULL);
			tmp_expand->type = WORD;
			expand_result = ft_token_append_list(expand_result, tmp_expand);
		}
		index++;
	}
	expand_result = ft_token_get_head(expand_result);
	tmp_expand = join_cmd_expand(expand_result);
	if (!tmp_expand)
		return (ft_free_char_tab(&splited_token), NULL);
	return (ft_free_char_tab(&splited_token), ft_token_free_list(&expand_result),
			tmp_expand);
}

/* cmd_list is the token_list from the cmd part of a t_simple_cmd 
 * Foreach token in the list it will replace it by the new token_list \
 * resulting from the PARAMETER_EXPENSION
 * Whiche means : 
 * expend is splited by <newline><tab><space> if not whitin double quote
 * RETURN 0 on SUCCESS / RETURN 1 ON ERROR
 * */
int	expand_cmd_list(t_token_list **cmd_list, char **env)
{
	t_token_list	*expanded_token;
	t_token_list	*index;

	if (!cmd_list)
		return (0);
	index = *cmd_list;
	while (index)
	{
		if (contain_expand(index->token))
		{
			expanded_token = expand_cmd_token(index->token, env);
			if (!expanded_token)
				return (1);
			index = ft_token_replace_by(&index, expanded_token);
			*cmd_list = index;
		}
		index = index->next;
	}
	*cmd_list = ft_token_get_head(*cmd_list);
	return (0);
}
