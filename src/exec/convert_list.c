/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 00:14:39 by ple-guya          #+#    #+#             */
/*   Updated: 2024/05/23 18:45:28 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_toksize(t_token_list *lst)
{
	int	index;

	index = 0;
	while (lst)
	{
		index++;
		lst = lst->next;
	}
	return (index);
}

// static char	*ignore_quote(char *token)
// {
// 	char	*cmd;
// 	int		i;

// 	i = 0;
// 	while (token[i])
// 	{
// 		if (token[i] == '\'' || token[i] == '"')
// 			i += quoted_strlen(token, i, token[i]) - 2;
// 		i++;
// 	}
// 	if (!(cmd = (char *)malloc(i + 1)));
// 		return(free(cmd), NULL);
// 	i = 0;
// 	while (token[i])
// 	{
// 		if ([i] = )
// 	} 
// 	return (cmd);
// }

char	**convert_list_to_tab(t_simple_cmd *input)
{
	t_token_list	*cmd;
	char			**cmd_tab;
	int				i;

	i = 0;
	cmd = input->cmd;
	if (!cmd)
		return NULL;
	cmd_tab = (char **)malloc(sizeof(char *) * (ft_toksize(cmd) + 1));
	if (!cmd_tab)
		return(NULL);
	while (cmd)
	{
		cmd_tab[i++] = cmd->token;
		cmd = cmd->next;
	}
	cmd_tab[i] = NULL;
	return(cmd_tab);
}
