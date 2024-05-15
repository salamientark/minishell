/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:26:14 by madlab            #+#    #+#             */
/*   Updated: 2024/05/15 14:26:44 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minishell.h"

// Get the len of the quoted string
static int	quoted_strlen(const char *input, char quote)
{
	int	len;

	len = 1;
	while (input[len])
	{
		if (input[len] == quote)
		{
			len++;
			break ;
		}
		len++;
	}
	return (len);
}

