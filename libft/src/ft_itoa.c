/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:48:02 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/17 12:32:59 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	ft_itoa_get_size(int nb)
{
	int	size;

	if (nb == 0)
		return (1);
	size = 0;
	if (nb < 0)
		size++;
	while (nb != 0)
	{
		nb /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int nb)
{
	char	*str;
	int		size;
	int		tmp;

	size = ft_itoa_get_size(nb);
	str = (char *)malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		nb = -nb;
		str[0] = '-';
	}
	if (nb == 0)
		str[0] = '0';
	str[size--] = 0;
	while (nb != 0)
	{
		tmp = nb % 10;
		if (tmp < 0)
			tmp = -tmp;
		str[size--] = (tmp + '0');
		nb /= 10;
	}
	return (str);
}
