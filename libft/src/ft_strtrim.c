/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:50:35 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/17 12:32:59 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static char	*ft_strndup(const char *s, size_t size)
{
	size_t	s_len;
	char	*s_cp;

	if (size > 0)
	{
		if (ft_strlen(s) > size)
			s_len = size;
		else
			s_len = ft_strlen(s);
		s_cp = (char *)malloc(sizeof(char) * (s_len + 1));
		if (s_cp)
		{
			*(s_cp + s_len) = 0;
			while (s_len-- > 0)
				*(s_cp + s_len) = *(s + s_len);
			return (s_cp);
		}
	}
	return (NULL);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	unsigned int	end_word;
	unsigned int	begin_word;

	if (!s1)
		return (NULL);
	begin_word = 0;
	while (*(s1 + begin_word) && ft_strchr(set, *(s1 + begin_word)))
		begin_word++;
	if (!(*(s1 + begin_word)))
		return (ft_strndup("", 2));
	end_word = ft_strlen(s1);
	while (ft_strrchr(set, *(s1 + end_word - 1)))
		end_word--;
	return (ft_strndup((s1 + begin_word), (end_word - begin_word)));
}
