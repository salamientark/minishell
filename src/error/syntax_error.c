/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 23:42:06 by madlab            #+#    #+#             */
/*   Updated: 2024/05/10 23:53:36 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/error.h"

// MAYBE ERROR ARE NOT WRITTEN WITH PRINTF
// BUT STD_ERROR INSTEAD
void	syntax_error(const char *token)
{
	printf("%s: syntax error near unexpected token '%s'\n", BASH, token);
	return ;
}

