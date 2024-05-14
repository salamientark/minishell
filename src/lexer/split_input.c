/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 11:04:26 by madlab            #+#    #+#             */
/*   Updated: 2024/05/14 22:41:09 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

static void	free_all(char ***input_tab_ptr, unsigned int size)
{
	unsigned int	index;

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

int	is_quote(const char c)
{
	if (c == DOUBLE_QUOTE)
		return (1);
	if (c == SINGLE_QUOTE)
		return (1)
	return (0);
}

int	quoted_strlen(const char *input, char quote)
{
	int	len;

	len = 1;
	while (input[len])
	{
		if (input[len] == quote)
		{
			len++;
			break ;
		}
		len++;
	}
	return (len);

}
int	skip_quote(const char **input_p, char quote)
{
	int	len;

	(*input_p) += 1;
	len = 1;
	while (**input_p)
	{
		if (**input_p == quote)
		{
			*input_p += 1;
			len += 1;
			break ;
		}
		len++;
		*input_p += 1;
	}
	return (len);

}

// static int	skip_delimiter(const char **input_p, char delimiter)
// {
// 	int	len;
// 	printf("Skip delimiter: delimiter = %c | **input_p == %c\n", delimiter, **input_p);
// 
// 	(*input_p) += 1;
// 	len = 1;
// 	while (**input_p && **input_p != '\n')
// 	{
// 		if (is_closing_delimiter(delimiter, **input_p))
// 		{
// 			*input_p += 1;
// 			len += 1;
// 			break ;
// 		}
// 		if (is_opening_delimiter(**input_p) && **input_p == DOUBLE_QUOTE)
// 			len += skip_delimiter(input_p, **input_p);
// 		len++;
// 		*input_p += 1;
// 	}
// 	printf("Skip delimiter: %d char\n", len);
// 	return (len);
// }

static unsigned int	count_input(const char *input)
{
	const char		*input_cp;
	unsigned int	word_count;

	input_cp = input;
	word_count = 0;
	while (*input_cp)
	{
		if (*input_cp == NEWLINE)
		{
			word_count++;
			input_cp++;
		}
		else if (is_quote(*input_cp))
			skip_quote(&input_cp, *input_cp);
		else
			input_cp++;
	}
	if (word_count == 0 && (input != input_cp))
		word_count++;
	return (word_count);
}

static char	*extract_input(const char **str_p)
{
	int		size;
	char	*input;

	size = 0;
	while((*str_p)[size] && (*str_p)[size] != '\n')
	{
		if (is_quote((*str_p)[size]))
			size += quoted_strlen(*str_p, (*str_p)[size]);
		else
			size++;
	}
	if ((*str_p)[size])
		size++;
	printf("word_size = %d\n", size);
	input = (char *)malloc(size + 1);
	if (!input)
		return (print_error("malloc", strerror(errno)), NULL);
	ft_strncpy(input, (char *)*str_p, size);
	input[size] = '\0';
	*str_p += size;
	return (input);
}

char	**split_input(const char *input)
{
	char		**input_tab;
	int			tab_size;
	int			index;

	if (!input)
		return (NULL);
	tab_size = count_input(input);
	printf("Word_count: %d\n", tab_size);
	if (tab_size == 0)
		return (NULL);
	input_tab = (char **)malloc(sizeof(char *) * (tab_size + 1));
	if (!input_tab)
		return (print_error("malloc", strerror(errno)), NULL);
	index = 0;
	while (index < tab_size)
	{
		input_tab[index] = extract_input(&input);
		if (!input_tab[index])
			return (free_all(&input_tab, index), NULL);
		index++;
	}
	input_tab[index] = NULL;
	return (input_tab);
}

