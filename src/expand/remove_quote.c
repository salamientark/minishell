/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:24:08 by madlab            #+#    #+#             */
/*   Updated: 2024/05/30 20:32:15 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	remove_quote_on_element(t_expand *elem)
{
	int		word_pos;
	int		diff;
	size_t	word_len;

	word_pos = 0;
	diff = 0;
	word_len = ft_strlen(elem->word);
	while (elem->word[word_pos + diff])
	{
		if (elem->quote[word_pos + diff] == 1)
		{
			elem->word[word_pos] = '\0';
			diff++;
		}
		else
		{
			elem->word[word_pos] = elem->word[word_pos + diff];
			word_pos++;
		}
	}
	memset(elem->word + word_pos, 0, word_len - word_pos);
	memset(elem->quote, 0, sizeof(int) * word_len);
}

void	remove_quote(t_expand **expand_tab)
{
	int	index;

	if (!expand_tab)
		return ;
	index = 0;
	while (expand_tab[index])
	{
		remove_quote_on_element(expand_tab[index]);
		index++;
	}
}
