/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:46:40 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/21 01:37:43 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
 
// ========= TESTING ======== 
static void	free_cmd_tab(t_simple_cmd ***cmd_tab)
{
	int	index;

	if (!*cmd_tab)
		return ;
	index = 0;
	while ((*cmd_tab)[index])
	{
		free_token_list(&(*cmd_tab)[index]->cmd);
		(*cmd_tab)[index]->cmd = NULL;
		free_token_list(&(*cmd_tab)[index]->redirect_from);
		(*cmd_tab)[index]->redirect_from = NULL;
		free_token_list(&(*cmd_tab)[index]->redirect_to);
		(*cmd_tab)[index]->redirect_to = NULL;
		free((*cmd_tab)[index]);
		(*cmd_tab)[index] = NULL;
		index++;
	}
	free(*cmd_tab);
	*cmd_tab = NULL;
}
/*
int	get_token_list_len(t_token_list *token_l)
{
	int	size;

	size = 0;
	if (!token_l)
		return (0);
	while (token_l)
	{
		size++;
		token_l = token_l->next;
	}
	return (size);
}

void	print_token_list(t_token_list *token_l)
{
	if (!token_l)
	{
		printf("No token_list\n");
		return ;
	}
	while (token_l->next)
	{
		printf("%s \001\033\[0;32m\002-> \001\033\[0m\002 ", token_l->token);
		token_l = token_l->next;
	}
	printf("%s\n", token_l->token);
}

char	*str_token_type(t_token_type type)
{
	if (type == WORD)
		return ("WORD");
	if (type == T_PIPE)
		return ("PIPE");
	if (type == T_LESS_THAN)
		return ("LESS_THAN");
	if (type == T_GREATER_THAN)
		return ("GREATER_THAN");
	if (type == T_LEFT_PARENTHESIS)
		return ("LEFT_PARENTHESIS");
	if (type == T_RIGHT_PARENTHESIS)
		return ("RIGHT_PARENTHESIS");
	if (type == T_AND)
		return ("AND");
	if (type == T_OR)
		return ("OR");
	if (type == T_APPEND)
		return ("APPEND");
	if (type == T_HERE_DOC)
		return ("HERE_DOC");
	return ("WTF");
}

void	print_detailled_token_list(t_token_list *token_l)
{
	if (!token_l)
	{
		printf("null\n");
		return ;
	}
	while (token_l->next)
	{
		printf("%s \001\033\[0;33m\002|\001\033\[0;m\002 %s \001\033\[0;32m\002-> \001\033\[0m\002 ",
				token_l->token, str_token_type(token_l->type));
		token_l = token_l->next;
	}
	printf("%s \001\033\[0;36m\002|\001\033\[0;m\002 %s \001\033\[0m\002\n",
				token_l->token, str_token_type(token_l->type));
}

void	print_simple_cmd(t_simple_cmd *cmd)
{
	printf("cmd: ");
	print_token_list(cmd->cmd);
	// print_detailled_token_list(cmd->cmd);
	printf("infile: ");
	print_token_list(cmd->redirect_from);
	// print_detailled_token_list(cmd->redirect_from);
	printf("outfile: ");
	print_token_list(cmd->redirect_to);
	// print_detailled_token_list(cmd->redirect_to);
}

void	print_simple_cmd_tab(t_simple_cmd **cmd_tab)
{
	int	index;

	if (!cmd_tab)
	{
		printf("no_simple_cmd_tab\n");
		return ;
	}
	index = 0;
	while (cmd_tab[index + 1])
	{
		print_simple_cmd(cmd_tab[index]);
		printf("\001\033\[0;33m\002          |          |          |\n \
         V          V          V\n\001\033\[0m\002");
		index++;
	}
	print_simple_cmd(cmd_tab[index]);
}
//  ===== END OF TESTING =====
*/
int	main(int ac, char **av, char **env)
{
	char	*input;
	char	**env_shell = env;
	char	**cmd_tab;
	t_simple_cmd	**input_tab;
	(void)ac;
	(void)av;
	(void)env;

	while ("this is the best minishell")
	{
		input = display_prompt();
		if (ft_strlen(input)> 0)
		{
			input_tab = parse_input(input);
			if (input_tab)
			{
				cmd_tab = convert_list_to_tab(*input_tab);
				isbuiltin(cmd_tab, env_shell);
				free_cmd_tab(&input_tab);
			}
			//lexer DONE
			//parser DONE
			//built-in NEARLY DONE
			//pipe
			//redirections
			//execution
			//expand
		}
		free(input);
	}
}
