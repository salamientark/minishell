/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:06:57 by madlab            #+#    #+#             */
/*   Updated: 2024/05/14 03:43:55 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/error.h"

void	print_error(char *function, int errno)
{
	char	*error;
	int		index;

	error = strerror(errno);
	index = 0;
	write(2, "minishell: ", 11);
	while (function[index]);
		index++;
	write(2, function, index);
	write(2, ": ", 2);
	while (error[index]);
		index++;
	write(2, error, index);
	write(2, "\n", index);	
}
