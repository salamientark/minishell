/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_all.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 08:28:07 by madlab            #+#    #+#             */
/*   Updated: 2024/05/22 16:03:00 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// static void	free_splited_token(char ***splited_token_p)
// {
// 	int	index;

// 	if (!splited_token_p || !(*splited_token_p))
// 		return ;
// 	index = 0;
// 	while ((*splited_token_p)[index])
// 	{
// 		if ((*splited_token_p)[index])
// 		{
// 			free((*splited_token_p)[index]);
// 			(*splited_token_p)[index] = NULL;
// 		}
// 		index++;
// 	}
// 	free(*splited_token_p);
// 	*splited_token_p = NULL;
// }

// int	contain_expand(const char *str)
// {
// 	int	index;
// 	int	in_double_quote;

// 	index = 0;
// 	if (!str || !str[index])
// 		return (0);
// 	in_double_quote = 0;
// 	while (str[index])
// 	{
// 		if (str[index] == DOUBLE_QUOTE)
// 		{
// 			in_double_quote = 1 ^ in_double_quote;
// 			index++;
// 		}
// 		else if (str[index] == SINGLE_QUOTE && in_double_quote == 0)
// 			index += quoted_strlen(str, index, str[index]);
// 		else if (is_expand(str + index))
// 			return (1);
// 		else
// 			index++;
// 	}
// 	return (0);
// }

// static char	*expand_token(const char *token, char **env)
// {
// 	char	**splited_token;
// 	char	*tmp_expand;
// 	char	*final_token;
// 	int		index;

// 	splited_token = split_expand(token);
// 	printf("\n\n\n");
// 	print_char_tab(splited_token);
// 	if (!splited_token)
// 		return (NULL);
// 	index = 0;
// 	while (splited_token[index])
// 	{
// 		if (is_expand(splited_token[index]))
// 		{
// 			tmp_expand = var_expand(splited_token[index], env);
// 			if (!tmp_expand)
// 				return (free_splited_token(&splited_token), NULL);
// 			free(splited_token[index]);
// 			splited_token[index] = tmp_expand;
// 		}
// 		index++;
// 	}
// 	final_token = join_splited_expand(splited_token);
// 	if (!final_token)
// 		return (free_splited_token(&splited_token), NULL);
// 	return (free_splited_token(&splited_token), final_token);
// }


int	expand_all(t_simple_cmd *cmd, char **env)
{
	int	expand_status;

	if (!cmd)
		return (0);
	expand_status = expand_cmd_list(&(cmd->cmd), env);
	if (expand_status != 0)
		return (expand_status);
// 	expand_status = expand_token_list(cmd->redirect_from, env);
// 	if (expand_status != 0)
// 		return (expand_status);
// 	expand_status = expand_token_list(cmd->redirect_to, env);
// 	if (expand_status != 0)
// 		return (expand_status);
	return (0);
}
