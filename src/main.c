/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:46:40 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/16 23:35:20 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ========= TESTING ======== 
# define NORMAL_COLOR_gt "\001\033\[m\002"
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

//  ===== END OF TESTING =====
static void	free_token_list(t_token_list **elem)
{
	t_token_list	*tmp_elem;

	if (!*elem)
		return ;
	while ((*elem)->prev)
		*elem = (*elem)->prev;
	while (*elem)
	{
		tmp_elem = (*elem)->next;
		free((*elem)->token);
		(*elem)->token = NULL;
		free((*elem));
		(*elem) = NULL;
		(*elem) = tmp_elem;
	}
	*elem = NULL;
}



int	main()
{
	char	*input;
	t_token_list	*token_list;

	while ("this is the best minishell")
	{
		input = display_prompt();
		// 		write(1, input, 4);
// 		write(1, "\n", 1);
		if (ft_strlen(input) > 0)
		{
			if (!unclosed_delimiter(input))
			{
				if (!first_pass(input))
				{
					token_list = tokenize(input);
					if (!token_list)
						printf("TOKEN LIST IS NULL\n");
					else
					{
						print_token_list(token_list);
						free_token_list(&token_list);
					}
				}
			}

			//lexer
			//parser
			//built-in
			//pipe
			//expand
			//redirections
			//execution
		}	
		free(input);
	}
}
