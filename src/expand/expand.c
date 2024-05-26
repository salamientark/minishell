/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 23:15:53 by madlab            #+#    #+#             */
/*   Updated: 2024/05/26 23:37:12 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

static void	free_all(t_expand **expand_p, int last_pos)
{
	int	index;

	index = 0;
	while (index < last_pos)
	{
		free((*expand_p)->type[index]);
		(*expand_p)->type[index] = NULL;
		index++;
	}
	free((*expand_p)->type);
	(*expand_p)->type = NULL;
	(*expand_p)->word_tab = NULL;
	free(*expand_p);
	*expand_p = NULL;
}

t_expand	*make_t_expand(char **tab, int cmd)
{
	t_expand	*expand;
	int			index;
	size_t		word_len;

	expand = (t_expand *)malloc(sizeof(struct s_expand));
	if (!expand)
		return (NULL);
	expand->cmd = cmd;
	expand->word_tab = tab;
	expand->type = (int **)malloc(sizeof(int) * ft_tab_size(tab));
	if (!expand->type)
		return (free(expand), NULL);
	index = 0;
	while (tab[index])
	{
		word_len = ft_strlen(tab[index]);
		expand->type[index] = (int *)malloc(sizeof(int) * word_len); 
		if (!expand->type[index])
			return (free_all(&expand, index), NULL);
		memset(expand->type[index], 1, word_len);
		index++;
	}
	return (expand);
}

int	expand(t_simple_cmd *cmd)
{
	t_expand	expand;

	expand = make_expand(cmd->cmd, 1);
	if (!expand)
		return (1);


// 	expand = make_expand(cmd->infile, 0);
// 	if (!expand)
// 		return (1);

// expand = make_expand(cmd->outfile, 0);
// if (!expand)
// 	return (1);
}
