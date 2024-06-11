/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 03:48:12 by madlab            #+#    #+#             */
/*   Updated: 2024/06/11 20:48:30 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

/* Properly free a single expand element
 * */
void	free_expand_elem(t_expand **expand_p)
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

/* Properly free a t_expand tab
 * */
void	free_expand_tab(t_expand ***expand_p)
{
	int	index;

	if (!expand_p || !(*expand_p))
		return ;
	index = 0;
	while ((*expand_p)[index])
	{
		if ((*expand_p)[index]->word)
		{
			free((*expand_p)[index]->word);
			(*expand_p)[index]->word = NULL;
		}
		free((*expand_p)[index]->quote);
		(*expand_p)[index]->quote = NULL;
		free((*expand_p)[index]);
		(*expand_p)[index] = NULL;
		index++;
	}
	free(*expand_p);
	*expand_p = NULL;
}
