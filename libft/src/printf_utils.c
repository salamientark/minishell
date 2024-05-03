/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 17:14:12 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/17 12:35:01 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf_opt.h"

int	nbr_base_len(long long n, int base)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n != 0)
	{
		n /= base;
		len++;
	}
	return (len);
}

unsigned int	make_nbr(const char **s)
{
	unsigned int	width;

	width = 0;
	while ('0' <= **s && **s <= '9')
	{
		width = 10 * width + (**s - 48);
		(*s)++;
	}
	return (width);
}

void	putnchar(const char c, int n)
{
	while (n-- > 0)
		write(1, &c, 1);
}
