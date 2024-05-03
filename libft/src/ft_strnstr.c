/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:34:10 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/17 12:32:59 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	index;
	size_t	s2_len;

	if (!(*s2))
		return ((char *)s1);
	index = 0;
	s2_len = ft_strlen(s2);
	while (index < len && s1[index])
	{
		if (ft_strlen(s2) > len - index)
			s2_len = len - index;
		else
			s2_len = ft_strlen(s2);
		if (!ft_strncmp(&s1[index], s2, s2_len) && !(*(s2 + s2_len)))
			return ((char *)(s1 + index));
		index++;
	}
	return (NULL);
}
