/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:33:49 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/17 12:32:59 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	index;
	size_t	res;

	res = ft_strlen(src);
	index = 0;
	if (siz > 0 && dst != NULL && src != NULL)
	{
		while (index < (siz - 1) && src[index])
		{
			dst[index] = src[index];
			index++;
		}
		dst[index] = '\0';
	}
	return (res);
}
