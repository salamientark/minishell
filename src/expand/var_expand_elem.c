/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expand_elem.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:51:30 by madlab            #+#    #+#             */
/*   Updated: 2024/05/30 16:20:01 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

/* Free the t_expand and make it point to NULL on error
 * */
static void	free_all(t_expand **expand_p)
{
	if ((*expand_p)->quote)
	{
		free((*expand_p)->quote);
		(*expand_p)->quote = NULL;
	}
	if ((*expand_p)->word)
	{
		free((*expand_p)->word);
		(*expand_p)->word = NULL;
	}
	free(*expand_p);
	*expand_p = NULL;
}

/* allocate a new t_expand element and every field of it, letting enough space
 * for the result of an expanded word given as an argument
 * */
static t_expand	*alloc_expanded_element(const char *word, char **env)
{
	t_expand	*final_expand;
	char		*final_str;
	int			*final_quote;
	size_t		final_strlen;

	final_strlen = expanded_variable_len(word, env);
	final_expand = (t_expand *)malloc(sizeof(struct s_expand));
	if (!final_expand)
		return (print_error("malloc", strerror(errno)), NULL);
	final_expand->size = final_strlen;
	if (final_strlen == 0)
		return (final_expand);
	final_str = (char *)malloc(final_strlen + 1);
	if (!final_str)
		return (print_error("malloc", strerror(errno)), free(final_expand),
			NULL);
	final_quote = (int *)malloc(sizeof(int) * final_strlen);
	if (!final_quote)
		return (print_error("malloc", strerror(errno)), free(final_str),
			free(final_expand), NULL);
	final_str[0] = '\0';
	memset(final_quote, 0, final_strlen);
	final_expand->word = final_str;
	final_expand->quote = final_quote;
	return (final_expand);
}

/* cat_unt_expand  concat the final_expand->word and the string from elem->word
 * starting at ref until it find an expansion.
 * * strating at elem->word[index]
 * It will update the 'quote' field and the index of elem->word
 * */
static t_expand	*cat_until_expand(t_expand *final_expand, t_expand *elem,
		int *ref)
{
	int	size;
	int	index;
	int	result_ref;

	size = *ref;
	while (elem->word[size] && !is_expand(elem->word + size))
	{
		if (elem->word[size] == SINGLE_QUOTE)
			size += quoted_strlen(elem->word, size, elem->word[size]);
		else
			size++;
	}
	size -= *ref;
	index = 0;
	result_ref = ft_strlen(final_expand->word);
	while (index < size)
	{
		final_expand->word[result_ref + index] = elem->word[*ref + index];
		final_expand->quote[result_ref + index] = elem->quote[*ref + index];
		index++;
	}
	final_expand->word[result_ref + index] = '\0';
	*ref += size;
	return (final_expand);
}

/* cat_expand concat the final_expand->word and the result of the expansion
 * strating at elem->word[index]
 * It will update the 'quote' field and the index of elem->word
 * */
static t_expand	*cat_expand(t_expand **final_expand, t_expand *elem, int *index,
		char **env)
{
	char	*expand_result;
	size_t	expand_result_len;
	size_t	final_word_len;

	expand_result = expand_variable(elem->word + *index, env);
	if (!expand_result)
		return (free_all(final_expand), NULL);
	expand_result_len = ft_strlen(expand_result);
	*index += (elem->word[*index + 1] == LEFT_BRACE)
		+ expand_strlen(elem->word, *index, 0);
	if (expand_result_len == 0)
		return (free(expand_result), *final_expand);
	final_word_len = ft_strlen((*final_expand)->word);
	memset((*final_expand)->word + final_word_len, 0, expand_result_len);
	(*final_expand)->word = ft_strcat((*final_expand)->word, expand_result);
	free(expand_result);
	return (*final_expand);
}

/* str_var_expand return a new t_expand * resulting from variable expansion
 * of the elem->word. Putting the correct value in the 'quote' field.
 * */
t_expand	*var_expand_elem(t_expand *elem, char **env)
{
	t_expand	*expand_result;
	int			index;
	char		*word_cp;

	expand_result = alloc_expanded_element(elem->word, env);
	if (!expand_result)
		return (NULL);
	if (expand_result->size == 0)
		return (expand_result);
	word_cp = elem->word;
	index = 0;
	while (word_cp[index])
	{
		if (!is_expand(word_cp + index))
			expand_result = cat_until_expand(expand_result, elem, &index);
		else
		{
			expand_result = cat_expand(&expand_result, elem, &index, env);
			if (!expand_result)
				return (NULL);
		}
	}
	return (expand_result);
}
