/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perform_variable_expansion.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 19:03:22 by madlab            #+#    #+#             */
/*   Updated: 2024/06/12 22:17:44 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

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

/* Remove element at pos index frm tab (element expanded to nothing)
 * */
static t_expand	**remove_from_tab(t_expand **dest, int remove_index)
{
	int	index;

	index = remove_index;
	free(dest[index]->word);
	dest[index]->word = NULL;
	free(dest[index]->quote);
	dest[index]->quote = NULL;
	free(dest[index]);
	dest[index] = NULL;
	while (dest[index + 1])
	{
		dest[index] = dest[index + 1];
		index++;
	}
	dest[index] = NULL;
	return (dest);
}

static int	variable_expansion(t_expand **expand_tab, int *index,
	t_chill *shell)
{
	t_expand	*expand_result;

	while (expand_tab[*index])
	{
		if (contain_var_expansion(expand_tab[*index]->word))
		{
			if (!is_valid_expand(expand_tab[*index]->word))
				return (1);
			expand_result = var_expand_elem(expand_tab[*index], shell);
			if (!expand_result)
				return (1);
			if (expand_result->size != 0)
			{
				free_expand_elem(&expand_tab[*index]);
				expand_tab[*index] = expand_result;
				*index += 1;
				continue ;
			}
			free(expand_result);
			expand_tab = remove_from_tab(expand_tab, *index);
		}
		*index += 1;
	}
	return (0);
}

/* Perform variable expansion for every element in the expand_tab
 * */
int	perform_variable_expansion(t_expand **expand_tab, t_chill *shell)
{
	int			index;

	index = 0;
	return (variable_expansion(expand_tab, &index, shell));
}
