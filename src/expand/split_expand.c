/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:25:41 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/21 17:35:32 by madlab           ###   ########.fr       */
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
	if (ft_isdigit(str[len]))
		return (len + 1);
	if (str[ref + len] && str[ref + len] == LEFT_BRACE)
	{
		len++;
		while (str[ref + len] && str[ref + len] != RIGHT_BRACE)
		{
			if (str[ref + len] == SINGLE_QUOTE
				|| str[ref + len] == DOUBLE_QUOTE)
				len += quoted_strlen(str, ref + len, str[ref + len]);
			else
				len++;
		}
		len += (str[ref + len] && str[ref + len] == RIGHT_BRACE);
		return (len);
	}
	while (str[ref + len]
		&& (ft_isalnum(str[ref + len]) || str[ref + len] == UNDERSCORE))
		len++;
	return (len);
}

static int	count_expand_word(const char *str)
{
	int	word_count;
	int	pos;
	int	in_double_quote;

	in_double_quote = 0;
	word_count = 1;
	pos = 0;
	while (str[pos])
	{
		if (str[pos] == DOUBLE_QUOTE)
			in_double_quote = 1 ^ in_double_quote;
		if (str[pos] == DOUBLE_QUOTE)
			pos++;
		else if (str[pos] == SINGLE_QUOTE && in_double_quote == 0)
			pos += quoted_strlen(str, pos, str[pos]);
		else if (is_expand(str + pos))
		{
			word_count += (pos != 0);
			pos += get_expand_len(str, pos);
			word_count += (str[pos] != '\0');
		}
		else
			pos++;
	}
	return (word_count);
}

static char	*extract_word(const char **str)
{
	int		word_len;
	char	*word;

	if (!*str)
		return (NULL);
	if (**str && **str == DOLLAR && (*str)[1] && !ft_isdigit(*((*str) + 1)))
		word_len = get_expand_len(*str, 0);
	else
	{
		word_len = 0;
		while ((*str)[word_len] && (!is_expand((*str) + word_len)))
		{
			if ((*str)[word_len] == SINGLE_QUOTE)
				word_len += quoted_strlen(*str, word_len, (*str)[word_len]);
			else
				word_len++;
		}
	}
	word = (char *)malloc(word_len + 1);
	if (!word)
		return (print_error("malloc", strerror(errno)), NULL);
	word = ft_strncpy(word, (char *)*str, word_len);
	word[word_len] = '\0';
	*str += word_len;
	return (word);
}

char	**split_expand(const char *str)
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
	expand_tab[word_count] = NULL;
	index = 0;
	while (index < word_count)
	{
		expand_tab[index] = extract_word(&str);
		if (!expand_tab[index])
			return (free_all(&expand_tab, index), NULL);
		index++;
	}
	return (expand_tab);
}
