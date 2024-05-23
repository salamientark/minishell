/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_var_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:27:45 by madlab            #+#    #+#             */
/*   Updated: 2024/05/23 01:43:34 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	contain_var_expansion(const char *str)
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

int	perform_var_expansion(char **tab, int cmd_flag, char **env)
{
	int		index;
	char	*expanded_word;

	(void) cmd_flag;
	index = 0;
	while (tab[index])
	{
		if (contain_var_expansion(tab[index]))
		{
			expanded_word = str_var_expansion(tab[index], env);
			if (!expanded_word)
				return (1);
			free(tab[index]);
			tab[index] = expanded_word;
		}
		index++;
	}
	return (0);
}
