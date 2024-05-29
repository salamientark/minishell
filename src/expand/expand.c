/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 23:15:53 by madlab            #+#    #+#             */
/*   Updated: 2024/05/29 18:46:12 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

// Properly free a t_expand**
void	free_expand_tab(t_expand ***expand_p)
{
	int	index;

	if (!expand_p || !(*expand_p))
		return ;
	index = 0;
	while ((*expand_p)[index])
	{
		// free((*expand_p)[index]->word);
		// (*expand_p)[index]->word = NULL;
		free((*expand_p)[index]->quote);
		(*expand_p)[index]->quote= NULL;
		free((*expand_p)[index]);
		(*expand_p)[index] = NULL;
		index++;
	}
	free(*expand_p);
	*expand_p = NULL;
}

// Perform every expansion of the t_simple_cmd then remove_quote
// In order :
//  - Variable expansion
//   - word splitting resulting from unquoted variable expansion
//  - pattern matching (BONUS)
//  - quote_removal
// On success return 0 else return 1
int	expand(t_simple_cmd *cmd)
{
	t_expand	**expand;

	expand = make_expand_tab(cmd->cmd);
	if (!expand)
		return (1);
	print_expand_tab(expand);
	free_expand_tab(&expand);
	return (0);

// 	expand = make_expand(cmd->infile, 0);
// 	if (!expand)
// 		return (1);

// expand = make_expand(cmd->outfile, 0);
// if (!expand)
// 	return (1);
}

// Create a t_expand type filling every expand->quote value with 1
// We will fill every expan->quote value resulting from expansion with 0
// t_expand	*make_t_expand(char **tab, int cmd)
// {
// 	t_expand	*expand;
// 	int			index;
// 	size_t		word_len;
// 
// 	expand = (t_expand *)malloc(sizeof(struct s_expand));
// 	if (!expand)
// 		return (NULL);
// 	expand->cmd = cmd;
// 	expand->word_tab = tab;
// 	expand->quote = (int **)malloc(sizeof(int) * ft_tab_size(tab));
// 	if (!expand->quote)
// 		return (free(expand), NULL);
// 	index = 0;
// 	while (tab[index])
// 	{
// 		word_len = ft_strlen(tab[index]);
// 		expand->quote[index] = (int *)malloc(sizeof(int) * word_len); 
// 		if (!expand->quote[index])
// 			return (free_all(&expand, index), NULL);
// 		memset(expand->quote[index], 1, word_len);
// 		index++;
// 	}
// 	return (expand);
// }
