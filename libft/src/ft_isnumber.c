/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:29:50 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/17 12:32:59 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_isnumber(char *s)
{
	int	index;

	if (!s)
		return (0);
	index = 0;
	if (s[0] == '-')
	{
		if ((!s[1]) || !ft_isdigit(s[1]))
			return (0);
		index++;
	}
	while (s[index])
	{
		if (!ft_isdigit(s[index]))
			return (0);
		index++;
	}
	return (1);
}
