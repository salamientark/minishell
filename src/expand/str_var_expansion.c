/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_var_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:00:56 by madlab            #+#    #+#             */
/*   Updated: 2024/05/29 01:11:27 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static int	set_split_flag(const char *str, int in_double_quote)
{
	int	index;

	if (!str)
		return (0);
	if (in_double_quote)
		return (0);
	index = 0;
	while (str[index])
	{
		if (is_space_metachar(str[index]))
			return (1);
		index++;
	}
	return (0);
}

static char	*cat_until_expand(char *dest, const char **word,
	int *in_double_quote)
{
	int	str_size;

	str_size = 0;
	while ((*word)[str_size] && !is_expand((*word) + str_size))
	{
		if ((*word)[str_size] == DOUBLE_QUOTE)
		{
			*in_double_quote = 1 ^ *in_double_quote;
			str_size++;
		}
		else if ((*word)[str_size] == SINGLE_QUOTE && *in_double_quote == 0)
			str_size += quoted_strlen((*word), str_size, (*word)[str_size]);
		else
			str_size++;
	}
	dest = ft_strncat(dest, (char *)*word, str_size);
	*word += str_size;
	return (dest);
}

static char	*alloc_final_str(const char *word, char **env)
{
	int		final_strlen;
	char	*final_str;

	final_strlen = var_expand_strlen(word, env);
	final_str = (char *)malloc(final_strlen + 1);
	if (!final_str)
		return (print_error("malloc", strerror(errno)), NULL);
	final_str[0] = '\0';
	return (final_str);
}

int	str_var_expansion(char **final_str, const char *word, int *split_flag,
	char **env)
{
	int		in_double_quote;
	char	*expand_result;

	*final_str = alloc_final_str(word, env);
	if (!(*final_str))
		return (1);
	in_double_quote = 0;
	while (*word)
	{
		if (!is_expand(word))
			(*final_str) = cat_until_expand((*final_str), &word,
					&in_double_quote);
		else
		{
			expand_result = NULL;
			if (expand_var(&expand_result, word, env) != 0)
				return (free((*final_str)), 1);
			*split_flag = set_split_flag(expand_result, in_double_quote);
			*final_str = ft_strcat(*final_str, expand_result);
			if (expand_result)
				free(expand_result);
			word += expand_strlen(word, 0, 0);
		}
	}
	return (0);
}
