/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:24:54 by marvin            #+#    #+#             */
/*   Updated: 2024/05/15 20:24:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_quote()
{
	
}

void	ft_echo(char **cmd)
{
	int i;
	int j;

	i = 1;
	while(cmd[i++])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == SINGLE_QUOTE || cmd[i][j] == DOUBLE_QUOTE)
				j += write_quote(cmd[i]);
			else
				ft_putchar_fd(cmd[i][j], 1);
			j++;
		}
	}
}
