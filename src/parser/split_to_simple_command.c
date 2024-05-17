/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_to_simple_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:24:04 by madlab            #+#    #+#             */
/*   Updated: 2024/05/17 03:52:02 by madlab           ###   ########.fr       */
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
		free_token_list(&(*cmd_tab[index])->cmd);
		(*cmd_tab[index])->cmd = NULL;
		free_token_list(&(*cmd_tab[index])->redirect_from);
		(*cmd_tab[index])->redirect_to = NULL;
		free_token_list(&(*cmd_tab[index])->redirect_to);
		(*cmd_tab[index])->redirect_from = NULL;
		free((*cmd_tab)[index]);
		index++;
	}
	free(*cmd_tab);
	*cmd_tab = NULL;
}

static int	count_command(t_token_list *token_list)
{
	t_token_list	*token_list_cp;
	int				simple_cmd_count;

	simple_cmd_count = 1;
	token_list_cp = token_list;
	while (token_list_cp)
	{
		if (token_list_cp->type == T_PIPE)
			simple_cmd_count++;
		token_list_cp = token_list_cp->next;
	}
	return (simple_cmd_count);
}

static t_simple_cmd	*get_simple_cmd(t_token_list **token_list_p)
{
	t_simple_cmd	*simple_cmd;
	t_token_list	*tmp_token;

	simple_cmd = (t_simple_cmd *)malloc(sizeof(struct s_simple_cmd));
	if (!simple_cmd)
		return (print_error("malloc", strerror(errno)), NULL);
	simple_cmd->cmd = NULL;
	simple_cmd->redirect_from = NULL;
	simple_cmd->redirect_to = NULL;
	while (*token_list_p && (*token_list_p)->type != T_PIPE)
	{
		if ((*token_list_p)->type == WORD)
		{
			tmp_token = (*token_list_p)->next;
			simple_cmd->cmd = add_token(simple_cmd->cmd, *token_list_p);
			simple_cmd->cmd->next = NULL;
			*token_list_p = tmp_token;
		}
		else
		{
			tmp_token = (*token_list_p)->next;
			tmp_token->type = (*token_list_p)->type;
			free((*token_list_p)->token);
			free((*token_list_p));
			if (tmp_token->type == T_LESS_THAN || tmp_token->type == T_HERE_DOC)
				simple_cmd->redirect_from = add_token(simple_cmd->redirect_from,
					tmp_token);
			else
				simple_cmd->redirect_to = add_token(simple_cmd->redirect_to, tmp_token);
			*token_list_p = tmp_token;
			*token_list_p = (*token_list_p)->next;
		}
	}
	if (*token_list_p)
	{
		tmp_token = (*token_list_p)->next;
		free((*token_list_p)->token);
		free((*token_list_p));
		*token_list_p = tmp_token;
	}
	simple_cmd->cmd = get_token_list_head(simple_cmd->cmd);
	simple_cmd->redirect_from = get_token_list_head(simple_cmd->redirect_from);
	simple_cmd->redirect_to = get_token_list_head(simple_cmd->redirect_to);
	return (simple_cmd);
}

t_simple_cmd	**split_to_simple_command(t_token_list **token_list_p)
{
	int				command_count;
	int				index;
	t_simple_cmd	**simple_cmd_tab;

	command_count = count_command(*token_list_p);
	printf("simple_command count : %d\n", command_count);
	simple_cmd_tab = (t_simple_cmd **)malloc(sizeof(struct s_simple_cmd*)
			* (command_count + 1));
	if (!simple_cmd_tab)
		return (print_error("malloc", strerror(errno)),
			free_token_list(token_list_p), NULL);
	index = 0;
	while (index < command_count)
	{
		simple_cmd_tab[index] =  get_simple_cmd(token_list_p);
		if (!simple_cmd_tab[index])
			return (free_all(&simple_cmd_tab, index), NULL);
		index++;
	}
	simple_cmd_tab[index] = NULL;
	return (simple_cmd_tab);
}
