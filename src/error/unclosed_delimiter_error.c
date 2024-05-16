/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_delimiter_error.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:13:15 by ple-guya          #+#    #+#             */
/*   Updated: 2024/05/16 17:13:23 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unclosed_delimiter_error(const char *str, int ref)
{
	write(2, BASH, 9);
	write(2, ": unclosed \'", 12);
	write(2, str + ref, 1);
	write(2, "\' at line ", 10);
	ft_putnbr_fd(ref, 2);
	write(2, "\n", 1);
}
