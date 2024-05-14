/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:46:40 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/14 22:41:19 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_input_tab(char ***input_tab)
{
	int	index;

	index = 0;
	while ((*input_tab)[index])
	{
		free((*input_tab)[index]);
		(*input_tab)[index] = NULL;
		index++;
	}
	free(*input_tab);
	*input_tab = NULL;
}

int	main()
{
	char	*input;
	char	**input_tab;

	while ("this is the best minishell")
	{
		input = display_prompt();
		/ 		write(1, input, 4);
// 		write(1, "\n", 1);
		if (ft_strlen(input) > 0)
		{
			input_tab = split_input(input);
			print_input(input_tab);
			free_input_tab(&input_tab);
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
