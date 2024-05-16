/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:06:57 by madlab            #+#    #+#             */
/*   Updated: 2024/05/15 21:35:34 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/error.h"

void	print_error(char *function, char *error)
{
	int	msg_len;

	write(2, "minishell: ", 11);
	msg_len = ft_strlen(function);
	write(2, function, msg_len);
	write(2, ": ", 2);
	msg_len = ft_strlen(error);
	write(2, error, msg_len);
	write(2, "\n", 1);
}
