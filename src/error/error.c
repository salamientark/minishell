/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:06:57 by madlab            #+#    #+#             */
/*   Updated: 2024/05/25 16:43:21 by ple-guya         ###   ########.fr       */
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
