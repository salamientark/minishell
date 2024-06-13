/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:46:40 by dbaladro          #+#    #+#             */
/*   Updated: 2024/06/13 16:29:52 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unlink_all(void)
{
	unlink("/tmp/.00000");
	unlink("/tmp/.00001");
	unlink("/tmp/.00002");
	unlink("/tmp/.00003");
	unlink("/tmp/.00004");
	unlink("/tmp/.00005");
	unlink("/tmp/.00006");
	unlink("/tmp/.00007");
	unlink("/tmp/.00008");
	unlink("/tmp/.00009");
	unlink("/tmp/.00010");
	unlink("/tmp/.00011");
	unlink("/tmp/.00012");
	unlink("/tmp/.00013");
	unlink("/tmp/.00014");
	unlink("/tmp/.00015");
}


// ========= TESTING ======== 
// static void	free_cmd_tab(t_simple_cmd ***cmd_tab)
// {
// 	int	index;

// 	if (!*cmd_tab)
// 		return ;
// 	index = 0;
// 	while ((*cmd_tab)[index])
// 	{
// 		ft_free_char_tab(&(*cmd_tab)[index]->cmd);
// 		(*cmd_tab)[index]->cmd = NULL;
// 		ft_free_char_tab(&(*cmd_tab)[index]->redirection);
// 		(*cmd_tab)[index]->redirection = NULL;
// 		free((*cmd_tab)[index]);
// 		(*cmd_tab)[index] = NULL;
// 		index++;
// 	}
// 	free(*cmd_tab);
// 	*cmd_tab = NULL;
// }

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
	printf("redirection: ");
	if (cmd->redirection)
		print_char_tab(cmd->redirection);
	else
		printf("(null)\n");
	// print_detailled_token_list(cmd->redirect_from);
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

void	print_expand_tab(t_expand **expand_tab)
{
	int	tab_index;
	int	index;

	if (!expand_tab || !*expand_tab)
	{
		printf("Expand tab is EMPTY\n");
		return ;
	}
	tab_index = 0;
	while (expand_tab[tab_index + 1])
	{
		printf("%s -> ", expand_tab[tab_index]->word);
		tab_index++;
	}
	printf("%s\n", expand_tab[tab_index]->word);
	tab_index = 0;
	while (expand_tab[tab_index + 1])
	{
		index = 0;
		while (expand_tab[tab_index]->word[index])
		{
			printf("%d", expand_tab[tab_index]->quote[index]);
			index++;
		}
		printf((" -> "));
		tab_index++;
	}
	index = 0;
	while (expand_tab[tab_index]->word[index])
	{
		printf("%d", expand_tab[tab_index]->quote[index]);
		index++;
	}
	printf("\n");
}


// int	*(*init_builtin_tab)()(result)
// {
// 	int		(*result[7])(char **, struct s_chill *);
// 
// 	result[0] = &ft_unset;
// // 	result[0] = &ft_cd;
// // 	result[1] = &ft_echo;
// // 	result[2] = &ft_env;
// // 	result[3] = &ft_exit;
// // 	result[4] = &ft_export;
// // 	result[5] = &ft_pwd;
// // 	result[6] = &ft_unset;
// 	return ((void *)result);
// }

// static void print_cmd(char **cmd)
// {
// 	int i = 0;
// 	while(cmd[i])
// 		printf("%s\n", cmd[i++]);
// }
//  ===== END OF TESTING =====

int	main(int ac, char **av, char **env)
{
	char			*input;
	t_chill			shell;
	(void)ac;
	(void)av;
	int				(*result[7])(char **, struct s_chill *);

//	result = init_builtin_tab(result);
 
	result[0] = &ft_unset;
	(void)result;
	init_minishell(&shell, env);
	while ("this is the best minishell")
	{
		unlink_all();
		input = display_prompt();
		// if (ft_strlen(input)> 0)
		// {
			shell.cmd_tab = parse_input(input, shell.env);
			if (shell.cmd_tab)
			{
				execution_cmd(&shell);
//				print_simple_cmd_tab(shell.cmd_tab);
//				free_cmd_tab(&shell.cmd_tab);
			}
			//lexer DONE
			//parser DONE
			//built-in NEARLY DONE
			//pipe
			//redirections
			//execution
	//	}
		free(input);
	}
	rl_clear_history();
	return (0);
}
