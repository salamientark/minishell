/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand_strlen.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:24:43 by madlab            #+#    #+#             */
/*   Updated: 2024/05/23 02:45:03 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	get_expand_len(const char *str, int ref)
{
	int	len;

	len = 1;
	if (!str || !*str)
		return (len);
	if (ft_isdigit(str[len]))
		return (len + 1);
	if (str[ref + len] && str[ref + len] == LEFT_BRACE)
	{
		len++;
		while (str[ref + len] && str[ref + len] != RIGHT_BRACE)
			len++;
		len += (str[ref + len] && str[ref + len] == RIGHT_BRACE);
		return (len);
	}
	while (str[ref + len]
		&& (ft_isalnum(str[ref + len]) || str[ref + len] == UNDERSCORE))
		len++;
	return (len);
}

static size_t	get_env_var_len(const char *str, int ref, char **env)
{
	size_t	key_len;
	int		index;

	key_len = 0;
	ref++;
	if (ft_isdigit(str[ref]))
		return (0);
	if (str[ref] == LEFT_BRACE)
		ref++;
	while (str[ref + key_len] && (ft_isalnum(str[ref + key_len])
			|| str[ref + key_len] == UNDERSCORE))
		key_len++;
	index = 0;
	while (env[index])
	{
		if (ft_strncmp(env[index], str + ref, key_len) == 0
			&& env[index][key_len] && env[index][key_len] == EQUAL)
			return (ft_strlen(&env[index][key_len + 1]));
		index++;
	}
	return (0);
}

static void	update_size_and_word(size_t *size, const char **word,
	int *in_double_quote)
{
	if (**word == DOUBLE_QUOTE)
	{
		*in_double_quote = 1 ^ *in_double_quote;
		*word += 1;
		*size += 1;
	}
	else if (**word == SINGLE_QUOTE && !(*in_double_quote))
	{
		*size += quoted_strlen(*word, 0, **word);
		*word += quoted_strlen(*word, 0, **word);
	}
	else
	{
		*word += 1;
		*size += 1;
	}
}

size_t	var_expand_strlen(const char *word, char **env)
{
	size_t	size;
	int		in_double_quote;

	size = 0;
	in_double_quote = 0;
	while (*word)
	{
		if (is_expand(word))
		{
			size += get_env_var_len(word, 0, env);
			word += get_expand_len(word, 0);
			continue ;
		}
		update_size_and_word(&size, &word, &in_double_quote);
	}
	return (size);
}
