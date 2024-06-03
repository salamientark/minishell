/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_here_doc_warning.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 22:35:30 by madlab            #+#    #+#             */
/*   Updated: 2024/06/02 22:36:08 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

/* Print HERE_DOC warning mesg when <EOF> is written
 * */
void	print_here_doc_warning(int line, char *limiter)
{
	int	limiter_len;

	limiter_len = 0;
	if (*limiter)
	{
		while (limiter[limiter_len] == NEWLINE)
			limiter_len++;
	}
	write(1, HERE_DOC_WARNING_MSG_1, 43);
	ft_putnbr_fd(line, 1);
	write(1, HERE_DOC_WARNING_MSG_2, 35);
	write(1, limiter, limiter_len);
	write(1, HERE_DOC_WARNING_MSG_3, 3);
}
