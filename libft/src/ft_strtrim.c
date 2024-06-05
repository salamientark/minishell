/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:50:35 by dbaladro          #+#    #+#             */
/*   Updated: 2024/06/05 18:32:31 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/* Allocates (with malloc(3)) and returns a copy of
 * ’s1’ with the characters specified in ’set’ removed
 * from the beginning and the end of the string.
 * */
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
