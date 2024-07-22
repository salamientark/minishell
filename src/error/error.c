/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 14:06:57 by madlab            #+#    #+#             */
/*   Updated: 2024/07/22 19:01:11 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	print_error_cmd(char *msg, char *arg, char *error)
{
	int		msg_len;
	int		arg_len;
	int		error_len;
	char	buffer[512];

	msg_len = ft_strlen(msg);
	arg_len = ft_strlen(arg);
	error_len = ft_strlen(error);
	ft_memcpy((void *)buffer, msg, msg_len);
	ft_memcpy((void *)buffer + msg_len, arg, arg_len);
	ft_memcpy((void *)buffer + msg_len + arg_len, ": ", 2);
	ft_memcpy((void *)buffer + msg_len + arg_len + 2, error, error_len);
	buffer[msg_len + arg_len + error_len + 2] = '\n';
	write(2, buffer, msg_len + error_len + arg_len + 3);
}
