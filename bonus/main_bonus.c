/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:46:40 by dbaladro          #+#    #+#             */
/*   Updated: 2024/06/13 11:50:01 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell_bonus.h"

int	g_signal = 0;

// ========= TESTING ======== 
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

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                           BINARY TREE PRINTING UTILS                      */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
// static int	ft_max(int a, int b)
// {
// 	if (a >= b)
// 		return (a);
// 	return (b);
// }

// static int	get_tree_depth(t_btree *root)
// {
// 	if (ft_btree_is_leaf(root))
// 		return (1);
// 	else
// 		return (1 + (ft_max(get_tree_depth(root->l_node),
// 			get_tree_depth(root->r_node))));
// }

# define COUNT 30
void	print_btree(t_btree *root, int space)
{
    if (root == NULL)
        return;
    space += COUNT;
    print_btree(root->r_node, space);
	printf("\n");
    for (int i = COUNT; i < space; i++)
		printf(" ");
	printf("%5s\n", (char *)root->content);
    print_btree(root->l_node, space);
}

//  ===== END OF TESTING =====
/*
 *
 *			PLEASE TO SYNTAX ERROR CHECKING BEFORE MAKE TREE
 *
 * */
int	main(int ac, char **av, char **env)
{
	t_chill	*shell;
	int		index;
	t_btree	*tree;
	(void)ac;
	(void)av;

	shell = init_shell(env);
	if (!shell)
		return (1);
	index = 0;
	while ("this is the best minishell")
	{
		unlink_here_doc();
		shell->input = display_prompt();
		if (!shell->input)
			break ;
		if (ft_strlen(shell->input) > 0)
		{
			tree = make_tree(shell->input, &index);
			if (!tree)
				return (exit_shell(shell, 1));
			print_btree(tree, 0);
			printf("\n\n\n\\t\t\t\t == GO EXEC TREE == \n\n");
			exec_tree_void(tree, shell);
			ft_btree_free_all(&tree);
		}
		free(shell->input);
	}
	ft_btree_free_all(&tree);
	return (exit_shell(shell, 0));
}
