/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:46:40 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/26 18:22:11 by madlab           ###   ########.fr       */
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
		ft_free_char_tab(&(*cmd_tab)[index]->cmd);
		(*cmd_tab)[index]->cmd = NULL;
		ft_free_char_tab(&(*cmd_tab)[index]->infile);
		(*cmd_tab)[index]->infile = NULL;
		ft_free_char_tab(&(*cmd_tab)[index]->outfile);
		(*cmd_tab)[index]->outfile = NULL;
		free((*cmd_tab)[index]);
		(*cmd_tab)[index] = NULL;
		index++;
	}
	free(*cmd_tab);
	*cmd_tab = NULL;
}

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
	if (type == T_EXPAND)
		return ("T_EXPAND");
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

void	print_char_tab(char **tab)
{
	int	index;

	if (!tab)
	{
		printf("print_char_tab : No tab\n");
		return ;
	}
	if (!(*tab))
	{
		printf("(null)\n");
		return ;
	}
	index = 0;
	while (tab[index + 1])
	{
		printf("%s -> ", tab[index]);
		index++;
	}
	printf("%s\n", tab[index]);
}

void	print_simple_cmd(t_simple_cmd *cmd)
{
	printf("cmd: ");
	if (cmd->cmd)
		print_char_tab(cmd->cmd);
	else
		printf("(null)\n");
	// print_detailled_token_list(cmd->cmd);
	printf("infile: ");
	if (cmd->infile)
		print_char_tab(cmd->infile);
	else
		printf("(null)\n");
	// print_detailled_token_list(cmd->redirect_from);
	printf("outfile: ");
	if (cmd->outfile)
		print_char_tab(cmd->outfile);
	else
		printf("(null)\n");
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

void	free_char_tab(char ***tab_p)
{
	int	index;

	if (!tab_p || !(*tab_p))
		return ;
	index = 0;
	while ((*tab_p)[index])
	{
		if ((*tab_p)[index])
		{
			free((*tab_p)[index]);
			(*tab_p)[index] = NULL;
		}
		index++;
	}
	free(*tab_p);
	*tab_p = NULL;
}

//  ===== END OF TESTING =====
int	main(int ac, char **av, char **env)
{
	char	*input;
	t_simple_cmd	**cmd_tab;
	(void)ac;
	(void)av;
	(void)env;

	while ("this is the best minishell")
	{
		input = display_prompt();
		if (ft_strlen(input)> 0)
		{
			cmd_tab = parse_input(input);
			printf("\n\n\n");
			if (cmd_tab)
			{
				printf("\001\033\[0;32m\002=== ORIGNAL CMD_TAB ===\001\033\[0m\n");
				print_simple_cmd_tab(cmd_tab);
// 				if (perform_var_expansion(&cmd_cmd, 1,  env) == 0)
// 					print_char_tab(cmd_cmd);
// 				else
// 					printf("EXPAND_ERROR\n");
// 				ft_free_char_tab(&cmd_cmd);
// 				printf("\n\001\033\[0;32m\002=== AFTER EXPAND ===\001\033\[0m\n");
				free_cmd_tab(&cmd_tab);
			}
			//lexer DONE
			//parser DONE
			//built-in DONE
			//expand DONE
			//pipe
			//redirections
			//execution
		}
		free(input);
	}
}
