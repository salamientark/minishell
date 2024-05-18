/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unclosed_delimiter_error.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 13:49:39 by madlab            #+#    #+#             */
/*   Updated: 2024/05/18 13:49:40 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	unclosed_delimiter_error(const char *str, int ref)
{
	write(2, BASH, 9);
	write(2, ": unclosed \'", 12);
	write(2, str + ref, 1);
	write(2, "\' at col ", 9);
	ft_putnbr_fd(ref, 2);
	write(2, "\n", 1);
}
