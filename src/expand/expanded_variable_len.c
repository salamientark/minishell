/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanded_variable_len.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 21:24:43 by madlab            #+#    #+#             */
/*   Updated: 2024/06/12 22:02:11 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

/* Get the key len (env key len)
 * */
int	get_expand_len(const char *str, int ref)
{
	int	len;

	len = 1;
	if (!str || !*str)
		return (len);
	if (str[len] == '?')
		return (len + 1);
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

/* get the len of one environment value
 * */
static size_t	get_env_var_len(const char *str, int ref, t_chill *shell)
{
	size_t	key_len;
	int		index;

	key_len = 0;
	ref++;
	if (ft_isdigit(str[ref]))
		return (0);
	if (str[ref] == LEFT_BRACE)
		ref++;
	if (str[ref] == '?')
		return (ft_nbrlen(shell->exit_status));
	while (str[ref + key_len] && (ft_isalnum(str[ref + key_len])
			|| str[ref + key_len] == UNDERSCORE))
		key_len++;
	index = 0;
	while (shell->env[index])
	{
		if (ft_strncmp(shell->env[index], str + ref, key_len) == 0
			&& shell->env[index][key_len] && shell->env[index][key_len] == '=')
			return (ft_strlen(&(shell->env[index][key_len + 1])));
		index++;
	}
	return (0);
}

/* Change the value of size and word after expand_len have been found
 * */
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

/* Get the value len (len of the word after expansion)
 * */
size_t	expanded_variable_len(const char *word, t_chill *shell)
{
	size_t	size;
	int		in_double_quote;

	size = 0;
	in_double_quote = 0;
	while (*word)
	{
		if (is_expand(word))
		{
			size += get_env_var_len(word, 0, shell);
			word += get_expand_len(word, 0);
			continue ;
		}
		update_size_and_word(&size, &word, &in_double_quote);
	}
	return (size);
}
