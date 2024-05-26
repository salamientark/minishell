/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:20:16 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/22 17:42:56 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <stdio.h>

static void	free_all(char ***str_tab_ptr, unsigned int size)
{
	while (size > 0)
	{
		free(*(str_tab_ptr[size]));
		*(str_tab_ptr[size--]) = 0;
	}
	free(*str_tab_ptr);
	*str_tab_ptr = 0;
}

static int	is_separator(const char c, char *sep)
{
	int	index;

	if (!sep)
		return (0);
	index = 0;
	while (sep[index])
	{
		if (c == sep[index])
			return (1);
		index++;
	}
	return (0);
}

static unsigned int	count_word(const char *str, char *sep)
{
	int			word_count;
	int			new_word;
	const char	*str_p;

	str_p = str;
	word_count = 0;
	new_word = 1;
	while (*str_p)
	{
		if (!is_separator(*str_p, sep))
		{
			if (new_word == 1)
				word_count++;
			new_word = 0;
		}
		else
			new_word = 1;
		str_p++;
	}
	return (word_count);
}

static char	*extract_word(const char **str, char *sep)
{
	int		i;
	int		size;
	char	*word;

	while (is_separator(**str, sep))
		(*str)++;
	i = 0;
	while ((*str)[i] && !is_separator((*str)[i], sep))
		i++;
	if (i == 0)
		return (NULL);
	word = (char *)malloc(i + 1);
	if (!word)
		return (NULL);
	size = i;
	i = 0;
	while (i < size)
	{
		word[i] = (*str)[i];
		i++;
	}
	word[i] = '\0';
	*str += size;
	return (word);
}

char	**ft_split_str(const char *s, char *sep)
{
	char			**strs_tab;
	unsigned int	word_nb;
	unsigned int	index;

	if (!s)
		return (NULL);
	word_nb = count_word(s, sep);
	strs_tab = (char **)malloc(sizeof(char *) * (word_nb + 1));
	if (!strs_tab)
		return (0);
	index = 0;
	while (index < word_nb)
	{
		strs_tab[index] = extract_word(&s, sep);
		if (!strs_tab[index])
		{
			free_all(&strs_tab, index);
			return (NULL);
		}
		index++;
	}
	strs_tab[index] = 0;
	return (strs_tab);
}
