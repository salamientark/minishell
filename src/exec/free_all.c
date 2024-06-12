/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:30:47 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/05 18:31:04 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
