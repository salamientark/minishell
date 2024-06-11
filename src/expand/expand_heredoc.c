/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:53:48 by madlab            #+#    #+#             */
/*   Updated: 2024/06/07 14:54:11 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

/* Perform variable expansion on heredoc input
 * */
char	*expand_heredoc(char *input, char **env)
{
	t_expand	**expand_tab;
	char		*result;
	int			index;

	index = 0;
	while (input[index] && !is_expand(input + index))
		index++;
	if (!input[index])
		return (input);
	expand_tab = (t_expand **)malloc(sizeof(t_expand *) * 2);
	if (!expand_tab)
		return (print_error("malloc", strerror(errno)), free(input), NULL);
	expand_tab[1] = NULL;
	expand_tab[0] = make_expand_elem(input);
	if (!expand_tab[0])
		return (free(expand_tab), free(input), NULL);
	ft_memset(expand_tab[0]->quote, 0, sizeof(int) * expand_tab[0]->size);
	expand_tab[1] = NULL;
	if (perform_variable_expansion(expand_tab, env) != 0)
		return (free_expand_tab(&expand_tab), free(input), NULL);
	result = expand_tab[0]->word;
	expand_tab[0]->word = NULL;
	free_expand_tab(&expand_tab);
	return (result);
}
