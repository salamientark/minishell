/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:32:52 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/17 12:32:59 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_atoi(const char *str)
{
	int	index;
	int	sign;
	int	nbr;

	nbr = 0;
	sign = 0;
	index = 0;
	while (str[index] == '\t' || str[index] == '\n' || str[index] == '\v'
		|| str[index] == '\f' || str[index] == '\r' || str[index] == ' ')
		index++;
	if (ft_isdigit(str[index]) == 0)
	{
		if (str[index] == '-')
			sign++;
		else if (str[index] != '+')
			return (0);
		index++;
	}
	while (ft_isdigit(str[index]) == 1)
		nbr = 10 * nbr + (str[index++] - 48);
	if (sign == 1)
		nbr *= -1;
	return (nbr);
}
