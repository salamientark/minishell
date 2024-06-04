/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:11:10 by madlab            #+#    #+#             */
/*   Updated: 2024/06/03 19:39:55 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_simple_cmd	**parse_input(const char *input, char **env)
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
	if (syntax_error(input, env))
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
