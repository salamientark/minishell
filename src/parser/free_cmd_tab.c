/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd_tab.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:54:28 by madlab            #+#    #+#             */
/*   Updated: 2024/06/22 15:36:32 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Properly free a t_simple_cmd **
 * */
void	free_cmd_tab(t_simple_cmd ***cmd_tab)
{
	int	index;

	if (!*cmd_tab)
		return ;
	index = 0;
	while ((*cmd_tab)[index])
	{
		ft_free_char_tab(&(*cmd_tab)[index]->cmd);
		(*cmd_tab)[index]->cmd = NULL;
		ft_free_char_tab(&(*cmd_tab)[index]->redirection);
		(*cmd_tab)[index]->redirection = NULL;
		free((*cmd_tab)[index]);
		(*cmd_tab)[index] = NULL;
		index++;
	}
	free(*cmd_tab);
	*cmd_tab = NULL;
}
