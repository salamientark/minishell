/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 23:15:53 by madlab            #+#    #+#             */
/*   Updated: 2024/07/23 14:44:51 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

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
int	perform_every_expansion(char ***word_tab_p, int cmd_flag,
		t_chill *shell)
{
	t_expand	**expand_tab;

	expand_tab = make_expand_tab(*word_tab_p);
	if (!expand_tab)
		return (1);
	if (perform_variable_expansion(expand_tab, shell) != 0)
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
int	expand(t_simple_cmd *cmd, t_chill *shell)
{
	if (perform_every_expansion(&cmd->cmd, 1, shell) != 0)
		return (1);
	if (perform_every_expansion(&cmd->redirection, 0, shell) != 0)
		return (1);
	return (0);
}
