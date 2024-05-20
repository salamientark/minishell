/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:25:41 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/21 00:14:23 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_all(char ***str_tab_p, int last_input)
{
	int	index;

	index = 0;
	while (index < last_input)
	{
		free((*str_tab_p)[index]);
		(*str_tab_p)[index] = NULL;
		index++;
	}
	free(*str_tab_p);
	*str_tab_p = NULL;
}

static int	get_expand_len(const char *str, int ref)
{
	int	len;

	len = 1;
	if (ft_isnbr(str[len]))
		return (len + 1);
	if (str[ref + len] && str[ref + index] == LEFT_BRACE)
	{
		len++;
		while (str[ref + len] && str[ref + len] != RIGHT_BRACE)
		{
			if (str[ref + len] == SINGLE_QUOTE
				|| str[ref + len] == DOUBLE_QUOTE)
				len += quoted_strlen(str, ref + index, str[ref + index]);
			else
				len++;
		}
		return (len);
	}
	while (str[ref + len]
		&& (ft_isalnum(str[ref + len]) || str[ref + index] == UNDERSCORE))
		len++;
	return (len);
}

static int	count_expand_word(const char *str)
{
	int	word_count;
	int	index;
	int	in_double_quote;

	word_count = 1;
	index = 0;
	while (str[index])
	{
		if (str[index] == DOUBLE_QUOTE)
			in_double_quote = 1 ^ in_double_quote;
		else if (str[index] == SINGLE_QUOTE && !in_double_quote)
			index += quoted_strlen(str, index, str[index]);
		else if (str[index] == DOLLAR && str[index + 1]
			&& !is_whitespace_metachar(str[index + 1]))
		{
			word_count++;
			index += get_expand_len(str, index);
		}
		else
			index++;
	}
	return (word_count);
}

static char	*extract_word(const char **str)
{
	int		word_len;
	char	*word;

	if (!*str)
		return (NULL);
	if (**str == DOLLAR && *(str + 1) && !ft_isnbr(*(str + 1)))
		word_len = get_expand_len(*str, ref);
	else
	{
		word_len = 0;
		while ((*str)[word_len] && !((*str)[word_len] == DOLLAR
			&& (*str)[word_len + 1] && !ft_isnbr((*str)[word_len + 1])))
		{
			if ((*str)[word_len] == SINGLE_QUOTE)
				word_len += quoted_strlen(*str, word_len, (*str)[word_len + 1]);
			else
				word_len++;
		}
	}
	word = (char *)malloc(word_size + 1);
	if (!word)
		return (print_error("malloc", strerror(errno)), NULL);
	word = ft_strncpy(word, *str, word_size);
	word[word_size] = '\0';
	return (word);
}

char	**split_expand(const char *str, const char **path)
{
	int		word_count;
	int		index;
	char	**expand_tab;

	if (!str)
		return (NULL);
	word_count = count_expand_word(str);
	expand_tab = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!expand_tab)
		return (print_error("malloc", strerror(errno)), NULL);
	index = 0;
	while (str[index])
	{
		expand_tab[index] = extract_word(&str);
		if (!expand_tab[index])
			return (free_all(&expand_tab, index), NULL);
		index++;
	}
	expand_tab[index] = NULL;
	return (expand_tab);
}
