/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 23:15:53 by madlab            #+#    #+#             */
/*   Updated: 2024/06/03 18:23:07 by dbaladro         ###   ########.fr       */
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

static int	expand_tab_to_char_tab(char ***result, t_expand ***expand_tab)
{
	int		index;
	char	**new_tab;

	*result = NULL;
	index = 0;
	while ((*expand_tab)[index])
		index++;
	new_tab = (char **)malloc(sizeof(char *) * (index + 1));
	if (!new_tab)
		return (print_error("malloc", strerror(errno)), 1);
	index = 0;
	while ((*expand_tab)[index])
	{
		free((*expand_tab)[index]->quote);
		new_tab[index] = (*expand_tab)[index]->word;
		free((*expand_tab)[index]);
		index++;
	}
	new_tab[index] = NULL;
	free(*expand_tab);
	*expand_tab = NULL;
	*result = new_tab;
	return (0);
}

/* Perform variable_expansion, word_split and quote removal on word_tab
 * cmd_flag is set to one if the cmd part is expanded
 * It indicates if the word_split should happened
 * */
static int	perform_every_expansion(char ***word_tab_p, int cmd_flag,
		char **env)
{
	t_expand	**expand_tab;

	expand_tab = make_expand_tab(*word_tab_p);
	if (!expand_tab)
		return (1);
	if (perform_variable_expansion(expand_tab, env) != 0)
		return (free_expand_tab(&expand_tab), 1);
	if (cmd_flag == 1 && perform_word_split(&expand_tab) != 0)
		return (free_expand_tab(&expand_tab), 1);
	remove_quote(expand_tab);
	free(*word_tab_p);
	*word_tab_p = NULL;
	if (expand_tab_to_char_tab(word_tab_p, &expand_tab) != 0)
		return (free_expand_tab(&expand_tab), 1);
	free_expand_tab(&expand_tab);
	return (0);
}

/* Perform expansion + quote_removal on every part of the t_simple_cmd
 * In order :
 *  - Variable expansion
 *  - word splitting resulting from unquoted variable expansion
 * - pattern matching (BONUS)
 * - quote_removal
 *  On success return 0 else return 1
 *  */
int	expand(t_simple_cmd *cmd, char **env)
{
	if (perform_every_expansion(&cmd->cmd, 1, env) != 0)
		return (1);
	if (perform_every_expansion(&cmd->redirection, 0, env) != 0)
		return (1);
	return (0);
}
