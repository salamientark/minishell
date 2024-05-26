/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_to_simple_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:24:04 by madlab            #+#    #+#             */
/*   Updated: 2024/05/26 13:18:45 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

// PLEASE REDO, IT HAVE TO FREE CHAR TAB 
static void	free_all(t_simple_cmd ***cmd_tab, int last_cmd)
{
	int	index;

	if (!*cmd_tab)
		return ;
	index = 0;
	while (index < last_cmd)
	{
		ft_free_char_tab(&(*cmd_tab)[index]->cmd);
		(*cmd_tab)[index]->cmd = NULL;
		ft_free_char_tab(&(*cmd_tab)[index]->redirect_from);
		(*cmd_tab)[index]->redirect_from = NULL;
		ft_free_char_tab(&(*cmd_tab)[index]->redirect_to);
		(*cmd_tab)[index]->redirect_to = NULL;
		free((*cmd_tab)[index]);
		(*cmd_tab)[index] = NULL;
		index++;
	}
	while ((*cmd_tab)[index])
	{
		free((*cmd_tab)[index]);
		(*cmd_tab)[index] = NULL;
		index++;
	}
	free(*cmd_tab);
	*cmd_tab = NULL;
}

static t_simple_cmd	*extract_redirection_token(t_simple_cmd *cmd,
		t_token_list **token_list)
{
	t_simple_cmd	*cmd_cp;
	t_token_list	*tmp_token;

	cmd_cp = cmd;
	tmp_token = (*token_list)->next;
	tmp_token->type = (*token_list)->type;
	free((*token_list)->token);
	(*token_list)->token = NULL;
	free((*token_list));
	(*token_list) = NULL;
	*token_list = tmp_token->next;
	if (tmp_token->type == T_LESS_THAN || tmp_token->type == T_HERE_DOC)
	{
		cmd_cp->redirect_from = add_token(cmd_cp->redirect_from, tmp_token);
		cmd_cp->here_doc_count += (tmp_token->type == HERE_DOC);
		cmd_cp->redirect_from->next = NULL;
	}
	else
	{
		cmd_cp->redirect_to = add_token(cmd_cp->redirect_to, tmp_token);
		cmd_cp->redirect_to->next = NULL;
	}
	return (cmd_cp);
}

static t_simple_cmd	*simple_cmd_end(t_simple_cmd *simple_cmd,
		t_token_list **token_list_p)
{
	t_token_list	*tmp_token;

	if (*token_list_p)
	{
		tmp_token = (*token_list_p)->next;
		free((*token_list_p)->token);
		(*token_list_p)->token = NULL;
		free((*token_list_p));
		(*token_list_p) = NULL;
		*token_list_p = tmp_token;
	}
	simple_cmd->cmd = get_token_list_head(simple_cmd->cmd);
	simple_cmd->redirect_from = get_token_list_head(simple_cmd->redirect_from);
	simple_cmd->redirect_to = get_token_list_head(simple_cmd->redirect_to);
	return (simple_cmd);
}

static void	get_cmd_param_size(int *cmd_size, int *infile_size,
	int *outfile_size, t_simple_cmd *token_list)
{
	t_token_list	+list_cp;

	*infile_size = 0;
	*outfile_size = 0;
	*cmd_size = 0;
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

static t_simple_cmd	*alloc_simple_cmd(t_token_list *token_list)
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
	cmd->infile = (char **)malloc(sizeof(char *) * infile_size);
	if (!cmd->infile)
		return (print_error("malloc", strerror(errno)), free(cmd), NULL);
	cmd->infile[infile_size] = NULL;
	cmd->outfile = (char **)malloc(sizeof(char *) * outfile_size);
	if (!cmd_outfile)
		return print_error("malloc", strerror(errno)), (free(cmd->infile),
			free(cmd), NULL);
	cmd->outfile[outfile_size] = NULL;
	cmd->cmd = (char **)malloc(sizeof(char *) * infile_size);
	if (!cmd->cmd)
		return (print_error("malloc", strerror(errno)), free(cmd->infile),
			free(cmd->outfile), free(cmd), NULL);
	cmd->cmd[cmd_size] = NULL;
	return (cmd);
}

static t_simple_cmd	add_redirection(t_simple_cmd cmd, int *infile_index,
	int *outfile_index, t_token_list **list_p)
{
	if ((*list_cp)->type == T_HERE_DOC || (*list_cp)->type == T_APPEND)
	{
		cmd->here_doc_count += ((*list_cp)->type == T_HERE_DOC);
		cmd->infile[*infile_index] = (*list_cp)->token;
		(*list_cp)->token = NULL;
		*infile_index++;
		(*list_cp) = (*list_cp)->next;
		cmd->infile[*infile_index] = (*list_cp)->token;
		(*list_cp)->token = NULL;
		*infile_index++;
		return (cmd);
	}
	cmd->outfile[*outfile_index] = (*list_cp)->token;
	(*list_cp)->token = NULL;
	*outfile_index++;
	(*list_cp) = (*list_cp)->next;
	cmd->outfile[*outfile_index] = (*list_cp)->token;
	(*list_cp)->token = NULL;
	*outfile_index++;
	return (cmd);

}

static t_simple_cmd	*get_simple_cmd(t_token_list **tok_list_p)
{
	t_simple_cmd	*simple_cmd;
	int				cmd_index;
	int				infile_index;
	int				outfile_index;

	simple_cmd = alloc_simple_cmd(*tok_list_p);
	if (!simple_cmd)
		return (free_token_list(tok_list_p), NULL);
	cmd_index = 0;
	infile_index = 0;
	outfile_index = 0;
	while (*tok_list_p && (*tok_list_p)->type != T_PIPE)
	{
		if ((*tok_list_p)->type == WORD)
		{
			simple_cmd[cmd_index] = (*tok_list_p)->token;
			(*tok_list_p)->token = NULL;
			cmd_index++;
		}
		else
			simple_cmd = add_redirection(simple_cmd, &infile_size,
				&outfile_size, tok_list_p);
		(*tok_list_p) = (*tok_list_p)->next;
	}
	return (simple_cmd);
}

t_simple_cmd	**split_to_simple_command(t_token_list **token_list_p)
{
	int				command_count;
	int				index;
	t_simple_cmd	**simple_cmd_tab;

	command_count = count_simple_command(*token_list_p);
	simple_cmd_tab = (t_simple_cmd **)malloc(sizeof(struct s_simple_cmd *)
			* (command_count + 1));
	if (!simple_cmd_tab)
		return (print_error("malloc", strerror(errno)),
			free_token_list(token_list_p), NULL);
	simple_cmd_tab[command_count] = NULL;
	index = 0;
	while (index < command_count)
	{
		simple_cmd_tab[index] = get_simple_cmd(token_list_p);
		if (*simple_cmd_tab[index])
			return (free_all(&simple_cmd_tab), NULL);
		index++;
	}
	return (simple_cmd_tab);
}

// static t_simple_cmd	*get_simple_cmd(t_token_list **token_list_p)
// {
// 	t_simple_cmd	*simple_cmd;
// 	t_token_list	*tmp_token;
// 
// 	simple_cmd = (t_simple_cmd *)malloc(sizeof(struct s_simple_cmd));
// 	if (!simple_cmd)
// 		return (print_error("malloc", strerror(errno)),
// 			free_token_list(token_list_p), NULL);
// 	simple_cmd->cmd = NULL;
// 	simple_cmd->redirect_from = NULL;
// 	simple_cmd->redirect_to = NULL;
// 	simple_cmd->here_doc_count = 0;
// 	while (*token_list_p && (*token_list_p)->type != T_PIPE)
// 	{
// 		if ((*token_list_p)->type == WORD)
// 		{
// 			tmp_token = (*token_list_p)->next;
// 			simple_cmd->cmd = add_token(simple_cmd->cmd, *token_list_p);
// 			simple_cmd->cmd->next = NULL;
// 			*token_list_p = tmp_token;
// 		}
// 		else
// 			simple_cmd = extract_redirection_token(simple_cmd, token_list_p);
// 	}
// 	return (simple_cmd_end(simple_cmd, token_list_p));
// }

// t_simple_cmd	**split_to_simple_command(t_token_list **token_list_p)
// {
// 	int				command_count;
// 	int				index;
// 	t_simple_cmd	**simple_cmd_tab;
// 
// 	command_count = count_simple_command(*token_list_p);
// 	simple_cmd_tab = (t_simple_cmd **)malloc(sizeof(struct s_simple_cmd *)
// 			* (command_count + 1));
// 	if (!simple_cmd_tab)
// 		return (print_error("malloc", strerror(errno)),
// 			free_token_list(token_list_p), NULL);
// 	simple_cmd_tab[command_count] = NULL;
// 	index = 0;
// 	while (index < command_count)
// 	{
// 		simple_cmd_tab[index] = get_simple_cmd(token_list_p);
// 		if (*token_list_p)
// 			(*token_list_p)->prev = NULL;
// 		if (!simple_cmd_tab[index])
// 			return (free_all(&simple_cmd_tab, index),
// 				free_token_list(token_list_p), NULL);
// 		index++;
// 	}
// 	return (simple_cmd_tab);
// }
