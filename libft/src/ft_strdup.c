/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:49:43 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/17 12:32:59 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s)
{
	size_t	s_len;
	char	*s_cp;

	s_len = ft_strlen(s);
	s_cp = (char *)malloc(sizeof(char) * (s_len + 1));
	if (s_cp != NULL)
	{
		*(s_cp + s_len) = 0;
		while (s_len-- > 0)
			*(s_cp + s_len) = *(s + s_len);
		return (s_cp);
	}
	return (NULL);
}
