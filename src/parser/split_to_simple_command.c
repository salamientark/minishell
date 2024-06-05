/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_to_simple_command.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 00:24:04 by madlab            #+#    #+#             */
/*   Updated: 2024/06/05 16:33:08 by dbaladro         ###   ########.fr       */
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
		ft_free_char_tab(&((*cmd_tab)[index]->cmd));
		(*cmd_tab)[index]->cmd = NULL;
		ft_free_char_tab(&((*cmd_tab)[index]->redirection));
		(*cmd_tab)[index]->redirection = NULL;
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

static int	count_simple_command(t_token_list *token_list)
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

static t_simple_cmd	*add_redirection(t_simple_cmd *cmd, int *redirection_index,
		t_token_list **list_p)
{
	cmd->redirection[*redirection_index] = (*list_p)->token;
	(*list_p)->token = NULL;
	*redirection_index += 1;
	(*list_p) = (*list_p)->next;
	cmd->redirection[*redirection_index] = (*list_p)->token;
	(*list_p)->token = NULL;
	*redirection_index += 1;
	return (cmd);
}

static t_simple_cmd	*add_simple_cmd(t_token_list **tok_list_p)
{
	t_simple_cmd	*simple_cmd;
	int				cmd_index;
	int				redirection_index;

	simple_cmd = alloc_simple_cmd(*tok_list_p);
	if (!simple_cmd)
		return (NULL);
	cmd_index = 0;
	redirection_index = 0;
	while (*tok_list_p && (*tok_list_p)->type != T_PIPE)
	{
		if ((*tok_list_p)->type == WORD)
		{
			simple_cmd->cmd[cmd_index] = (*tok_list_p)->token;
			(*tok_list_p)->token = NULL;
			cmd_index++;
		}
		else
			simple_cmd = add_redirection(simple_cmd, &redirection_index,
					tok_list_p);
		(*tok_list_p) = (*tok_list_p)->next;
	}
	return (simple_cmd);
}

t_simple_cmd	**split_to_simple_command(t_token_list **token_list_p)
{
	int				command_count;
	int				index;
	t_simple_cmd	**simple_cmd_tab;
	t_token_list	*list_head;

	list_head = *token_list_p;
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
		simple_cmd_tab[index] = add_simple_cmd(token_list_p);
		if (!simple_cmd_tab[index])
			return (free_all(&simple_cmd_tab, index), NULL);
		if (*token_list_p && (*token_list_p)->type == T_PIPE)
			*token_list_p = (*token_list_p)->next;
		index++;
	}
	*token_list_p = list_head;
	return (simple_cmd_tab);
}
