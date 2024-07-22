/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:30:47 by ple-guya          #+#    #+#             */
/*   Updated: 2024/07/22 23:53:40 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_redir(char **redir)
{
	char	**cpy;
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (redir[size])
		size++;
	if (size == 0)
		return (NULL);
	cpy = malloc(sizeof(char *) * (size + 1));
	if (!cpy)
		return (NULL);
	while (redir[i])
	{
		cpy[i] = ft_strdup(redir[i]);
		i++;
	}
	cpy[i] = NULL;
	return (cpy);
}

void	free_str_tab(char ***str_tab_ptr)
{
	int	index;

	index = 0;
	while ((*str_tab_ptr)[index] != NULL)
	{
		free((*str_tab_ptr)[index]);
		(*str_tab_ptr)[index] = NULL;
		index++;
	}
	free(*str_tab_ptr);
	*str_tab_ptr = NULL;
}
