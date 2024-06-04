/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:31:54 by madlab            #+#    #+#             */
/*   Updated: 2024/05/22 23:29:34 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_expand(const char *str)
{
	int	index;

	if (!str)
		return (0);
	index = 0;
	if (str[index] == DOLLAR && str[index + 1]
		&& (ft_isalnum(str[index + 1]) || str[index + 1] == UNDERSCORE
			|| str[index + 1] == LEFT_BRACE))
		return (1);
	return (0);
}
