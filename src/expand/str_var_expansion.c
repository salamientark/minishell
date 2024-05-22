/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_var_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:00:56 by madlab            #+#    #+#             */
/*   Updated: 2024/05/22 23:33:07 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

static char	*cat_expansion(char **final_str, const char **word, char **env)
{
	char	*expand_result;

	expand_result = expand_var(*word, env);
	if (!expand_result)
	{
		print_error("malloc", strerror(errno));
		free(*final_str);
		*final_str = NULL;
		return (*final_str);
	}
	*word += get_expand_len(*word, 0);
	*final_str = ft_strcat(*final_str, expand_result);
	free(expand_result);
	return (*final_str);
}

char	*str_var_expansion(const char *word, char **env)
{
	int		in_double_quote;
	int		final_strlen;
	char	*final_str;

	final_strlen = var_expand_strlen(word, env);
	final_str = (char *)malloc(final_strlen + 1);
	if (!final_str)
		return (print_error("malloc", strerror(errno)), NULL);
	final_str[0] = '\0';
	in_double_quote = 0;
	while (*word)
	{
		if (!is_expand(word))
			final_str = cat_until_expand(final_str, &word, &in_double_quote);
		else
		{
			final_str = cat_expansion(&final_str, &word, env);
			if (!final_str)
				return (NULL);
		}
	}
	return (final_str);
}
