/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:46:40 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/14 19:15:39 by dbaladro         ###   ########.fr       */
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
		free(input);
	}
}
