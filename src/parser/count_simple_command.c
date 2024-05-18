/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 12:44:41 by madlab            #+#    #+#             */
/*   Updated: 2024/05/18 13:10:21 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	count_simple_command(t_token_list *token_list)
{
	t_token_list	*token_list_cp;
	int				simple_cmd_count;

	simple_cmd_count = 1;
	token_list_cp = token_list;
	while (token_list_cp)
	{
		if (token_list_cp->type == T_PIPE)
			simple_cmd_count++;
		token_list_cp = token_list_cp->next;
	}
	return (simple_cmd_count);
}
