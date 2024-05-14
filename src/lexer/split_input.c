/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 11:04:26 by madlab            #+#    #+#             */
/*   Updated: 2024/05/14 11:41:14 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static void	free_all(char ***input_tab_ptr, unsigned int size)
{
	int	index;

	index = 0;
	while (index < size)
	{
		free(*(input_tab_ptr[index]));
		*(input_tab_ptr[index]) = NULL;
		index++;
	}
	free(*input_tab_ptr);
	*input_tab_ptr = NULL;
}

static int	skip_delimiter(const char **input_p, char delimiter)
{
	int	len;

	*input_p++;
	len = 1;
	while (**input_p)
	{
		if (is_closing_delimiter(delimiter, **input_p))
		{
			len++;
			break ;
		}
		if (is_opening_delimiter(**input_p))
			len += skip_delimiter(input_p, **input_p);
	}
	return (len);
}

static unsigned int	count_input(const char *input)
{
	const char		*input_cp;
	unsigned int	word_count;

	word_count = 1;
	while (*input_cp)
	{
		if (*input_cp == NEWLINE)
			word_count++;
		if (is_opening_delimiter(*input_cp))
			skip_delimiter(&input_cp, *input_cp);
		*input_cp++;
	}
	return (word_count);
}

static char	*extract_input(const char **str_p)
{
	int		size;
	char	*input;

	while((*str_p)[size] && (*str_p)[size] != '\n')
	{
		if (is_opening_delimiter(*(*str_p + size)))
			size += skip_delimiter(str_p, (*str_p)[size]);
		else
			size++;
	}
	if ((*str_p)[size])
		size++;
	input = (char *)malloc(size + 1);
	if (!input)
		return (print_error("malloc", errno), NULL);
	ft_strncpy(input, *str_p, size);
	*str_p += size;
	return (input);
}

char	**split_input(const char *input)
{
	char		**input_tab;
	int			tab_size;
	int			index;

	tab_size = count_input(input);
	if (tab_size == 0)
		return (NULL);
	input_tab = (char **)malloc(sizeof(char *) * (tab_size + 1));
	if (!input_tab)
		return (print_error("malloc", errno), NULL);
	index = 0;
	while (index < tab_size)
	{
		input_tab[index] = extract_input(&input_cp);
		if (!input_tab[index])
			return (free_all(&input_tab, index), NULL);
		index++;
	}
	input_tab[index] = NULL;
	return (input_tab);
}

