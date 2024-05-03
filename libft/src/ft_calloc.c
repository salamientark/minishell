/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:47:44 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/17 12:32:59 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_calloc(size_t nelem, size_t elsize)
{
	size_t	size;
	void	*mem;

	size = nelem * elsize;
	if (size == 0 || (size >= nelem && size >= elsize))
	{
		mem = (void *)malloc(size);
		if (mem)
			return (ft_memset(mem, '\0', size));
	}
	return (NULL);
}
