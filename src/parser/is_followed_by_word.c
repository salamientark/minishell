/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_followed_by_word.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:48:06 by dbaladro          #+#    #+#             */
/*   Updated: 2024/07/19 16:40:25 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

int	is_followed_by_word(const char *cmd, int operator)
{
	int	index;

	index = 1;
	if (operator == HERE_DOC)
		operator = LESS_THAN;
	if (operator == APPEND)
		operator = GREATER_THAN;
	if (!cmd[index]
		|| (operator == RIGHT_PARENTHESIS && cmd[index] == operator))
		return (0);
	if (cmd[index] && cmd[index] == operator)
		index++;
	while (cmd[index] && (cmd[index] == SPACE || cmd[index] == TAB))
		index++;
	if (!cmd[index] || cmd[index] == '\n')
		return (0);
	if (get_operator(cmd + index) != 0)
		return (0);
	return (1);
}
