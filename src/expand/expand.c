/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 23:15:53 by madlab            #+#    #+#             */
/*   Updated: 2024/05/29 12:55:42 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

// Properly free a t_expand*
static void	free_expand(t_expand **expand_p)
{
	int	index;

	if (!expand_p || !(*expand_p))
		return ;
	index = 0;
	while ((*expand_p)->word_tab[index])
	{
		free((*expand_p)->word_tab[index]);
		(*expand_p)->word_tab[index] = NULL;
		free((*expand_p)->quote[index]);
		(*expand_p)->quote[index] = NULL;
		index++;
	}
	free((*expand_p)->quote);
	(*expand_p)->quote = NULL;
	free(*expand_p);
	*expand_p = NULL;
}

// Properly free the t_expand_type on error
static void	free_all(t_expand **expand_p, int last_pos)
{
	int	index;

	index = 0;
	while (index < last_pos)
	{
		if ((*expand_p)->quote[index])
		{
			free((*expand_p)->quote[index]);
			(*expand_p)->quote[index] = NULL;
		}
		index++;
	}
	free((*expand_p)->quote);
	(*expand_p)->quote = NULL;
	(*expand_p)->word_tab = NULL;
	free(*expand_p);
	*expand_p = NULL;
}


static void	fill_expand_quote(t_expand *expand, char *str, int expand_index)
{
	int	str_index;

	if (!str)
		return ;
	str_index = 0;
	while (str[str_index])
	{
		expand->quote[expand_index][str_index] = 0;
		str_index++;
	}
	str_index = 0;
	while (str[str_index])
	{
		if (str[str_index] == DOUBLE_QUOTE || str[str_index] == SINGLE_QUOTE)
		{
			expand->quote[expand_index][str_index] = 1;
			str_index += quoted_strlen(str, str_index, str[str_index]) - 1;
			expand->quote[expand_index][str_index] = 1;
		}
		else
			expand->quote[expand_index][str_index] = 0;
		str_index++;
	}
}
// Create a t_expand element fill the type part using the following rule :
// If the quote should be remove at the end of expansion -> Set 0
// Else -> Set 1
// We will fill every expan->quote value resulting from expansion with 0
static t_expand	*make_t_expand(char **tab, int cmd_flag)
{
	t_expand	*expand;
	int			index;
	size_t		word_len;

	expand = (t_expand *)malloc(sizeof(struct s_expand));
	if (!expand)
		return (NULL);
	expand->cmd_flag = cmd_flag;
	expand->word_tab = tab;
	expand->quote = (int **)malloc(sizeof(int *) * ft_tab_size(tab));
	if (!expand->quote)
		return (free(expand), NULL);
	index = 0;
	while (tab[index])
	{
		word_len = ft_strlen(tab[index]);
		expand->quote[index] = (int *)malloc(sizeof(int) * word_len); 
		if (!expand->quote[index])
			return (free_all(&expand, index), NULL);
		fill_expand_quote(expand, tab[index], index);
		index++;
	}
	return (expand);
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

// Perform every expansion of the t_simple_cmd then remove_quote
// In order :
//  - Variable expansion
//   - word splitting resulting from unquoted variable expansion
//  - pattern matching (BONUS)
//  - quote_removal
// On success return 0 else return 1

int	expand(t_simple_cmd *cmd)
{
	t_expand	*expand;

	expand = make_t_expand(cmd->cmd, 1);
	print_expand(expand);
	if (!expand)
		return (1);
	free_expand(&expand);
	return (0);

// 	expand = make_expand(cmd->infile, 0);
// 	if (!expand)
// 		return (1);

// expand = make_expand(cmd->outfile, 0);
// if (!expand)
// 	return (1);
}
