/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_var_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:27:45 by madlab            #+#    #+#             */
/*   Updated: 2024/05/23 12:38:53 by madlab           ###   ########.fr       */
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

static char	**replace_by(char **final_tab, char **word_tab,
	char **splited_word, int *replace_index)
{
	int		index;

	index = 0;
	while (index < *replace_index)
	{
		final_tab[index] = word_tab[index];
		index++;
	}
	free(word_tab[index]);
	index = 0;
	while (splited_word[index])
	{
		final_tab[(*replace_index) + index] = splited_word[index];
		index++;
	}
	index = 0;
	while (word_tab[(*replace_index) + index + 1])
	{
		final_tab[*replace_index + index] = word_tab[*replace_index
			+ index + 1];
		index++;
	}
	return (final_tab);
}

static char	**perform_word_split(char ***tab, char *expanded_word, int *index)
{
	size_t	final_tab_size;
	char	**splited_word;
	char	**final_tab;

	splited_word = word_split(expanded_word);
	if (!splited_word)
		return (ft_free_char_tab(tab), free(expanded_word), NULL);
	final_tab_size = ft_tab_size(*tab) + ft_tab_size(splited_word);
	final_tab = (char **)malloc(sizeof(char *) * (final_tab_size));
	final_tab[final_tab_size] = NULL;
	if (!final_tab)
		return (print_error("malloc", strerror(errno)), ft_free_char_tab(tab),
			ft_free_char_tab(&splited_word), NULL);
	final_tab = replace_by(final_tab, *tab, splited_word, index);
	free(*tab);
	free(splited_word);
	return (final_tab);
}

int	perform_var_expansion(char ***tab, int cmd_flag, char **env)
{
	int		index;
	int		split_flag;
	char	*expanded_word;

	index = 0;
	while ((*tab)[index])
	{
		if (contain_var_expansion((*tab)[index]))
		{
			split_flag = 0;
			expanded_word = str_var_expansion((*tab)[index], &split_flag, env);
			if (!expanded_word)
				return (1);
			free((*tab)[index]);
			(*tab)[index] = expanded_word;
			if (cmd_flag && split_flag)
			{
				*tab = perform_word_split(tab, expanded_word, &index);
				if (!(*tab))
					return (1);
			}
		}
		index++;
	}
	return (0);
}
