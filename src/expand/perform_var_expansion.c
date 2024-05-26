/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_var_expansion.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:27:45 by madlab            #+#    #+#             */
/*   Updated: 2024/05/26 10:34:18 by madlab           ###   ########.fr       */
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

static void	remove_from_tab(char ***tab, int ref)
{
	int	index;

	index = ref;
	while (tab[index + 1])
	{
		tab[index] = tab[index + 1];
		index++;
	}
	tab[index] = NULL;
}

static char	**replace_by(char **final_tab, char **word_tab,
	char **splited_word, int *replace_index)
{
	int		word_index;
	int		index;

	word_index = 0;
	while (word_index < *replace_index)
	{
		final_tab[word_index] = word_tab[word_index];
		word_index++;
	}
	free(word_tab[word_index]);
	index = 0;
	while (splited_word[index])
	{
		final_tab[(*replace_index)] = splited_word[index];
		index++;
		*replace_index += 1;
	}
	index = 0;
	while (word_tab[word_index + 1 + index])
	{
		final_tab[*replace_index + index] = word_tab[word_index + 1 + index];
		index++;
	}
	final_tab[*replace_index + index] = NULL;
	return (final_tab);
}

static int	perform_word_split(char ***tab, char *expanded_word, int *index)
{
	size_t	final_tab_size;
	char	**splited_word;
	char	**final_tab;

	splited_word = word_split(expanded_word);
	if (!splited_word)
		return (ft_free_char_tab(tab), free(expanded_word), 1);
	final_tab_size = ft_tab_size(*tab) + ft_tab_size(splited_word);
	final_tab = (char **)malloc(sizeof(char *) * (final_tab_size));
	if (!final_tab)
		return (print_error("malloc", strerror(errno)), ft_free_char_tab(tab),
			ft_free_char_tab(&splited_word), 1);
	final_tab[final_tab_size - 1] = NULL;
	final_tab = replace_by(final_tab, *tab, splited_word, index);
	free(*tab);
	free(splited_word);
	*index -= 1;
	*tab = final_tab;
	return (0);
}

static int	expand_and_split(char ***tab, int cmd_flag, int *index, char **env)
{
	int		split_flag;
	char	*expanded_word;

	split_flag = 0;
	expanded_word = NULL;
	if (str_var_expansion(&expanded_word, (*tab)[*index], &split_flag,
		env) != 0)
		return (1);
	free((*tab)[*index]);
	(*tab)[*index] = expanded_word;
	if (!(*tab)[*index])
		remove_from_tab(tab, *index);
	if (cmd_flag && split_flag)
	{
		if (perform_word_split(tab, expanded_word, index) != 0)
			return (1);
	}
	return (0);
}

int	perform_var_expansion(char ***tab, int cmd_flag, char **env)
{
	int		index;

	index = 0;
	while ((*tab)[index])
	{
		printf("perf car expan index %d\n", index);
		if (contain_var_expansion((*tab)[index]))
		{
			if (expand_and_split(tab, cmd_flag, &index, env) != 0)
				return (1);
			if (!(*tab))
				return (0);
		}
		index++;
	}
	return (0);
}
