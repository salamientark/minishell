/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:31:54 by madlab            #+#    #+#             */
/*   Updated: 2024/05/21 14:44:38 by madlab           ###   ########.fr       */
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
		&& !is_space_metachar(str[index + 1]) && !ft_isdigit(str[index + 1]))
		return (1);
	return (0);
}
