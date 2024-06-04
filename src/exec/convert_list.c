/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 00:14:39 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/04 14:36:55 by ple-guya         ###   ########.fr       */
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
