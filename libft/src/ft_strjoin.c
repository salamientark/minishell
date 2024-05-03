/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:49:48 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/17 12:32:59 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*f_str;

	if (s1 == NULL)
		return ((char *)s2);
	if (s2 == NULL)
		return ((char *)s1);
	f_str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!f_str)
		return (NULL);
	*f_str = 0;
	ft_strlcat(f_str, s1, ft_strlen(s1) + 1);
	ft_strlcat(f_str + (ft_strlen(s1)), s2, ft_strlen(s2) + 1);
	return (f_str);
}
