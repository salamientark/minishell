/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:33:29 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/17 12:32:59 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;
	size_t			index;

	s1_ptr = (unsigned char *)s1;
	s2_ptr = (unsigned char *)s2;
	index = 0;
	while (index++ < n)
	{
		if (*s1_ptr > *s2_ptr)
			return ((int)(*s1_ptr - *s2_ptr));
		if (*s1_ptr < *s2_ptr)
			return ((int)(*s1_ptr - *s2_ptr));
		s1_ptr++;
		s2_ptr++;
	}
	return (0);
}
