/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_size.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 01:18:57 by madlab            #+#    #+#             */
/*   Updated: 2024/05/23 01:23:07 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_tab_size(char **tab)
{
	size_t	size;

	if (!tab)
		return (0);
	size = 0;
	while (tab[size])
		size++;
	return (size);
}
