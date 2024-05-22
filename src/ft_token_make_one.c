/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_make_one.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 13:30:49 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/22 16:09:14 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_token_list	*ft_token_make_one(char *input, t_token_type type)
{
	t_token_list	*new_token;

	new_token = (t_token_list *)malloc(sizeof(struct s_token_list));
	if (!new_token)
		return (print_error("malloc", strerror(errno)), NULL);
	new_token->token = input;
	new_token->size = ft_strlen(input);
	new_token->type = type;
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}
