/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:26:14 by madlab            #+#    #+#             */
/*   Updated: 2024/05/16 16:48:06 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Return the len of quoted word + 2 for quote OR
// -1 when no quote found 
int	quoted_strlen(const char *str, int ref, const char quote)
{
	int	len;

	len = 1;
	while (str[ref + len] && str[ref + len] != quote)
		len++;
	if (!str[ref + len])
		return (unclosed_delimiter_error(str, ref), -1);
	return (len + 1);
}
