/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:56:59 by madlab            #+#    #+#             */
/*   Updated: 2024/05/21 17:30:08 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	expand_error(const char *word)
{
	int	index;

	index = 2;
	if (word[index] && (word[index] == RIGHT_BRACE || ft_isdigit(word[index])))
		return (print_error((char *)word, "bad substitution"), 1);
	while (word[index] && word[index] != RIGHT_BRACE)
	{
		if (word[index] == SINGLE_QUOTE || word[index] == DOUBLE_QUOTE
			|| can_be_operator(word[index] || word[index] == LEFT_PARENTHESIS
				|| word[index] == RIGHT_PARENTHESIS || word[index] == LEFT_BRACE
					|| word[index] == ASTERISK))
			return (print_error((char *)word, "bad substitution"), 1);
		if (!ft_isalnum(word[index]) && word[index] != UNDERSCORE)
			break ;
		index++;
	}
	return (0);
}

static int	get_key_len(const char *to_expand)
{
	int	len;

	len = 0;
	while (to_expand[len] && (ft_isalnum(to_expand[len])
		|| to_expand[len] == UNDERSCORE))
		len++;
	return (len);
}

static char	*get_env_val(const char *key, int key_len, char **env)
{
	int		index;
	int		val_len;
	char	*value;

	index = 0;
	val_len = 0;
	while (env[index])
	{
		if (ft_strncmp(key, env[index], key_len) == 0
			&& env[index][key_len]
				&& env[index][key_len] == EQUAL)
		{
			while (env[index][key_len + 1 + val_len])
				val_len++;
			break ;
		}
		index++;
	}
	value = (char *)malloc(val_len + 1);
	if (!value)
		return (print_error("malloc", strerror(errno)), NULL);
	value[val_len] = '\0';
	if (val_len == 0)
		return (value);
	value = ft_strcpy(value, &(env[index][key_len + 1]));
	return (value);
}

char	*var_expand(const char *to_expand, char **env)
{
	int		ref;
	int		key_len;
	char	*env_val;

	ref = 1;
	if (to_expand[ref] && to_expand[ref] == LEFT_BRACE)
	{
		ref++;
		if (expand_error(to_expand))
			return (NULL);
		key_len = get_key_len(to_expand + ref);
	}
	else
		key_len = get_key_len(to_expand + ref);
	env_val = get_env_val(to_expand + ref, key_len, env);
	if (!env_val)
		return (NULL);
	return (env_val);
}
