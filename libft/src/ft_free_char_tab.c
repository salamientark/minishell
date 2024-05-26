/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_char_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:14:20 by madlab            #+#    #+#             */
/*   Updated: 2024/05/22 15:17:14 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_free_char_tab(char ***tab_p)
{
	int	index;

	if (!tab_p || !(*tab_p))
		return ;
	index = 0;
	while ((*tab_p)[index])
	{
		if ((*tab_p)[index])
		{
			free((*tab_p)[index]);
			(*tab_p)[index] = NULL;
		}
		index++;
	}
	free(*tab_p);
	*tab_p = NULL;
}
