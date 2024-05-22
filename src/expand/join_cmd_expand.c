/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmd_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:57:11 by madlab            #+#    #+#             */
/*   Updated: 2024/05/22 16:55:36 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static size_t	joined_token_strlen(t_token_list *src)
{
	size_t			total_str_len;
	t_token_type	first_token_type;
	t_token_list	*src_cp;

	total_str_len = 0;
	if (!src)
		return (total_str_len);
	first_token_type = src->type;
	total_str_len += ft_strlen(src->token);
	src_cp = src->next;
	while (src_cp && src_cp->type != T_EXPAND)
	{
		total_str_len += ft_strlen(src_cp->token);
		src_cp = src_cp->next;
	}
	if (first_token_type == WORD && src_cp && src_cp->type == T_EXPAND)
		total_str_len += ft_strlen(src_cp->token);
	return (total_str_len);
}

static char	*join_token_to_str(t_token_list **src_p)
{
	t_token_list	*src_cp;
	t_token_type	first_token_type;
	size_t			final_strlen;
	char			*final_str;

	if (!src_p && !(*src_p))
		return (NULL);
	final_strlen = joined_token_strlen(*src_p);
	final_str = (char *)malloc(final_strlen + 1);
	if (!final_str)
		return (print_error("malloc", strerror(errno)), NULL);
	final_str[0] = '\0';
	first_token_type = (*src_p)->type;
	final_str = ft_strcat(final_str, (*src_p)->token);
	src_cp = (*src_p)->next;
	while (src_cp && src_cp->type != T_EXPAND)
	{
		final_str = ft_strcat(final_str, src_cp->token);
		src_cp = src_cp->next;
	}
	*src_p = src_cp;
	if (first_token_type == WORD && src_cp && src_cp->type == T_EXPAND)
	{
		final_str = ft_strcat(final_str, src_cp->token);
		*src_p = src_cp->next;
	}
	return (final_str);
}

t_token_list	*join_cmd_expand(t_token_list *src)
{
	t_token_list	*final_token_list;
	t_token_list	*tmp_token;
	char			*joined_token;


	print_detailled_token_list(src);
// 	if (remove_quote(src) != 0)
// 		return (NULL);
	final_token_list = NULL;
	while (src)
	{
		joined_token = join_token_to_str(&src);
		if (!joined_token)
			return (ft_token_free_list(&final_token_list), NULL);
		tmp_token = ft_token_make_one(joined_token, T_EXPAND);
		if (!tmp_token)
			return (ft_token_free_list(&final_token_list), free(joined_token),
				NULL);
		final_token_list = ft_token_insert_list(final_token_list, tmp_token);
		if (!src)
			break ;
	}
	final_token_list = ft_token_get_head(final_token_list);
	return (final_token_list);
}
