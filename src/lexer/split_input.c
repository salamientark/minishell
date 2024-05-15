/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 11:04:26 by madlab            #+#    #+#             */
/*   Updated: 2024/05/15 02:40:03 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* split_input will split the input based on '\n' char
 * EX :
 * $> ls 
 *    cat
 *    ls
 * IS equivqlent to
 * $> ls
 * $> cat
 * $> ls
 * ---
 * $> ls |
 *    
 *    
 *    cat
 *  IS equivalent to 
 *  $> ls | cat
 * */

#include "../../includes/parser.h"

// Free on error
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

// Get the len of the quoted string
static int	quoted_strlen(const char *input, char quote)
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

int	is_closing_delimiter(const char c, const char delimiter)
{
	if (delimiter == LEFT_PARENTHESIS && c == RIGHT_PARENTHESIS)
		return (1);
	if (delimiter == LEFT_BRACE && c == RIGHT_BRACE)
		return (1);
	return (0);
}

int	is_operator(const char *str)
{
	if (*str == PIPE)
		return (1);
	if (*str == AMPERSAND && *(str + 1) && *(str + 1) == AMPERSAND)
		return (1);
	if (*str == LEFT_PARENTHESIS)
		return (1);
	if (*str == LEFT_BRACE && *(str + 1)
			&& (*(str + 1) == SPACE || *(str + 1) == TAB))
		return (1);
	return (0);
}

static unsigned int	count_input(const char *input)
{
	const char		*input_cp;
	unsigned int	word_count;
	char			operator;

	input_cp = input;
	word_count = 1;
	operator = 0;
	while (*input_cp)
	{
		// If opened ( or { and closing char encontered -> operator = 0
		if ((operator == LEFT_BRACE || operator == LEFT_PARENTHESIS)
				&& is_closing_delimiter(*input_cp, operator))
			operator = 0;
		// If '|' next line is following
		if (*input_cp == PIPE && operator == 0 && ((*(input_cp + 1)
				&& *(input_cp + 1) != PIPE) || !*(input_cp + 1)))
			operator = PIPE;
		// If operator == pipe && word is following -> operator == 0
		if (operator == PIPE && *input_cp != PIPE && !is_space_metachar(*input_cp))
			operator = 0;
		// IF newline and no operator or '{' or '(' add_word
		if (*input_cp == NEWLINE && operator == 0)
		{
			word_count++;
			input_cp++;
		}
		// IF quote -> SKip quote
		if (*input_cp == SINGLE_QUOTE || *input_cp == DOUBLE_QUOTE)
			input_cp += quoted_strlen(input_cp, *input_cp);
		// IF '(' || "{ " wait for closing ')' or '}'
		if (*input_cp == LEFT_PARENTHESIS || (*input_cp == LEFT_BRACE
				&& *(input_cp + 1) && (*(input_cp + 1) == SPACE
					|| *(input_cp + 1) == TAB)))
			operator = *input_cp;
		input_cp++;
	}
	return (word_count);
}

static char	*extract_input(const char **str_p)
{
	int		size;
	char	*input;
	int		pipe;

	size = 0;
	pipe = 0;
	while ((*str_p)[size] && !((*str_p)[size] == '\n' && pipe == 0))
	{
		if ((*str_p)[size] == PIPE || (*str_p)[size] == AMPERSAND)
			pipe = 1;
		if ((*str_p)[size] != PIPE && (*str_p)[size] != AMPERSAND
				&& !is_space_metachar((*str_p)[size]))
			pipe = 0;
		if ((*str_p)[size] == SINGLE_QUOTE || (*str_p)[size] == DOUBLE_QUOTE)
			size += quoted_strlen(*str_p, (*str_p)[size]);
		size++;
	}
	size += ((*str_p)[size] != '\0');
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
