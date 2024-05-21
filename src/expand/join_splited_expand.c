/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_splited_expand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:13:36 by madlab            #+#    #+#             */
/*   Updated: 2024/05/21 16:53:15 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static size_t	total_str_len(char **splited_expand)
{
	size_t	total_size;
	int		index;

	total_size = 0;
	if (!splited_expand)
		return (total_size);
	index = 0;
	while (splited_expand[index])
	{
		total_size += ft_strlen(splited_expand[index]);
		index++;
	}
	return (total_size);
}

char	*join_splited_expand(char **splited_expand)
{
	char	*joined_str;
	size_t	joined_strlen;
	int		index;

	joined_strlen = total_str_len(splited_expand);
	joined_str = (char *)malloc(joined_strlen + 1);
	if (!joined_str)
		return (print_error("malloc", strerror(errno)), NULL);
	joined_str[0] = '\0';
	if (joined_strlen == 0)
		return (joined_str);
	index = 0;
	while (splited_expand[index])
	{
		joined_str = ft_strcat(joined_str, splited_expand[index]);
		index++;
	}
	return (joined_str);
}
