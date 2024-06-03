/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_simple_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 18:29:30 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/26 18:44:02 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	get_cmd_param_size(size_t *cmd_size, size_t *infile_size,
	size_t *outfile_size, t_token_list *token_list)
{
	t_token_list	*list_cp;

	*infile_size = 0;
	*outfile_size = 0;
	*cmd_size = 0;
	list_cp = token_list;
	while (list_cp && list_cp->type != T_PIPE)
	{
		if (list_cp->type == T_LESS_THAN || list_cp->type == T_HERE_DOC)
		{
			*infile_size += 2;
			list_cp = list_cp->next;
		}
		else if (list_cp->type == T_GREATER_THAN || list_cp->type == T_APPEND)
		{
			*outfile_size += 2;
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
	size_t			infile_size;
	size_t			outfile_size;
	size_t			cmd_size;

	cmd = (t_simple_cmd *)malloc(sizeof(struct s_simple_cmd));
	if (!cmd)
		return (print_error("malloc", strerror(errno)), NULL);
	cmd->here_doc_count = 0;
	get_cmd_param_size(&cmd_size, &infile_size, &outfile_size, token_list);
	cmd->infile = (char **)malloc(sizeof(char *) * (infile_size + 1));
	if (!cmd->infile)
		return (print_error("malloc", strerror(errno)), free(cmd), NULL);
	cmd->infile[infile_size] = NULL;
	cmd->outfile = (char **)malloc(sizeof(char *) * (outfile_size + 1));
	if (!cmd->outfile)
		return (print_error("malloc", strerror(errno)), free(cmd->infile),
			free(cmd), NULL);
	cmd->outfile[outfile_size] = NULL;
	cmd->cmd = (char **)malloc(sizeof(char *) * (cmd_size + 1));
	if (!cmd->cmd)
		return (print_error("malloc", strerror(errno)), free(cmd->infile),
			free(cmd->outfile), free(cmd), NULL);
	cmd->cmd[cmd_size] = NULL;
	return (cmd);
}
