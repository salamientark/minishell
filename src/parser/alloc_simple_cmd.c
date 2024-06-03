/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:29:30 by dbaladro          #+#    #+#             */
/*   Updated: 2024/06/03 18:23:28 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	get_cmd_param_size(size_t *cmd_size, size_t *redirection_size,
	t_token_list *token_list)
{
	t_token_list	*list_cp;

	*redirection_size = 0;
	*cmd_size = 0;
	list_cp = token_list;
	while (list_cp && list_cp->type != T_PIPE)
	{
		if (list_cp->type == T_LESS_THAN || list_cp->type == T_HERE_DOC
			|| list_cp->type == T_GREATER_THAN || list_cp->type == T_APPEND)
		{
			*redirection_size += 2;
			list_cp = list_cp->next;
		}
		else
			*cmd_size += 1;
		list_cp = list_cp->next;
	}
}

t_simple_cmd	*alloc_simple_cmd(t_token_list *token_list)
{
	t_simple_cmd	*cmd;
	size_t			redirection_size;
	size_t			cmd_size;

	cmd = (t_simple_cmd *)malloc(sizeof(struct s_simple_cmd));
	if (!cmd)
		return (print_error("malloc", strerror(errno)), NULL);
	get_cmd_param_size(&cmd_size, &redirection_size, token_list);
	cmd->redirection = (char **)malloc(sizeof(char *) * (redirection_size + 1));
	if (!cmd->redirection)
		return (print_error("malloc", strerror(errno)), free(cmd), NULL);
	cmd->redirection[redirection_size] = NULL;
	cmd->cmd = (char **)malloc(sizeof(char *) * (cmd_size + 1));
	if (!cmd->cmd)
		return (print_error("malloc", strerror(errno)), free(cmd->redirection),
			free(cmd), NULL);
	cmd->cmd[cmd_size] = NULL;
	return (cmd);
}
