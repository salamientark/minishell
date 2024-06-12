/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:23:29 by madlab            #+#    #+#             */
/*   Updated: 2024/06/12 14:25:10 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_nbrlen(const int nbr)
{
	size_t	len;
	int		nb_cp;

	len = 1;
	nb_cp = nbr;
	while (nb_cp != 0)
	{
		nb_cp /= 10;
		len++;
	}
	return (len);
}
