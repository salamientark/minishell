/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_to_simple_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:24:04 by madlab            #+#    #+#             */
/*   Updated: 2024/05/22 13:27:27 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_all(t_simple_cmd ***cmd_tab, int last_cmd)
{
	int	index;

	if (!*cmd_tab)
		return ;
	index = 0;
	while (index < last_cmd)
	{
		ft_token_free_list(&(*cmd_tab)[index]->cmd);
		(*cmd_tab)[index]->cmd = NULL;
		ft_token_free_list(&(*cmd_tab)[index]->redirect_from);
		(*cmd_tab)[index]->redirect_from = NULL;
		ft_token_free_list(&(*cmd_tab)[index]->redirect_to);
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
		cmd_cp->redirect_from = ft_token_add_back(cmd_cp->redirect_from, tmp_token);
		cmd_cp->redirect_from->next = NULL;
	}
	else
	{
		cmd_cp->redirect_to = ft_token_add_back(cmd_cp->redirect_to, tmp_token);
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
	simple_cmd->cmd = ft_token_get_head(simple_cmd->cmd);
	simple_cmd->redirect_from = ft_token_get_head(simple_cmd->redirect_from);
	simple_cmd->redirect_to = ft_token_get_head(simple_cmd->redirect_to);
	return (simple_cmd);
}

static t_simple_cmd	*get_simple_cmd(t_token_list **token_list_p)
{
	t_simple_cmd	*simple_cmd;
	t_token_list	*tmp_token;

	simple_cmd = (t_simple_cmd *)malloc(sizeof(struct s_simple_cmd));
	if (!simple_cmd)
		return (print_error("malloc", strerror(errno)),
			ft_token_free_list(token_list_p), NULL);
	simple_cmd->cmd = NULL;
	simple_cmd->redirect_from = NULL;
	simple_cmd->redirect_to = NULL;
	while (*token_list_p && (*token_list_p)->type != T_PIPE)
	{
		if ((*token_list_p)->type == WORD)
		{
			tmp_token = (*token_list_p)->next;
			simple_cmd->cmd = ft_token_add_back(simple_cmd->cmd, *token_list_p);
			simple_cmd->cmd->next = NULL;
			*token_list_p = tmp_token;
		}
		else
			simple_cmd = extract_redirection_token(simple_cmd, token_list_p);
	}
	return (simple_cmd_end(simple_cmd, token_list_p));
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
			ft_token_free_list(token_list_p), NULL);
	simple_cmd_tab[command_count] = NULL;
	index = 0;
	while (index < command_count)
	{
		simple_cmd_tab[index] = get_simple_cmd(token_list_p);
		if (*token_list_p)
			(*token_list_p)->prev = NULL;
		if (!simple_cmd_tab[index])
			return (free_all(&simple_cmd_tab, index),
				ft_token_free_list(token_list_p), NULL);
		index++;
	}
	return (simple_cmd_tab);
}
