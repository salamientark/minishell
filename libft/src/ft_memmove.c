/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:33:32 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/17 12:32:59 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*dest_ptr;
	size_t	index;

	if (!dest && !src)
		return (NULL);
	dest_ptr = (char *)dest;
	if (dest_ptr < (char *)src)
	{
		index = 0;
		while (index++ < n)
			*(dest_ptr++) = *(char *)src++;
	}
	else
	{
		while (n--)
			*(dest_ptr + n) = *(char *)(src + n);
	}
	return (dest);
}
