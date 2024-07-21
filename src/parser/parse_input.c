/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:11:10 by madlab            #+#    #+#             */
/*   Updated: 2024/07/18 13:39:40 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_simple_cmd	**parse_input(const char *input, t_chill *shell)
{
	t_token_list	*token_list;
	t_simple_cmd	**simple_cmd_tab;

	if (heredoc_count(input) > 16)
	{
		write(2, HERE_DOC_COUNT_EXCEEDED, 48);
		return (NULL);
	}
	if (unclosed_delimiter(input))
		return (NULL);
	if (syntax_error(input, shell) != 0)
		return (NULL);
	token_list = tokenize(input);
	if (!token_list)
		return (NULL);
	simple_cmd_tab = split_to_simple_command(&token_list);
	ft_token_free_list(&token_list);
	if (!simple_cmd_tab)
		return (NULL);
	return (simple_cmd_tab);
}
