/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:46:40 by ple-guya          #+#    #+#             */
/*   Updated: 2024/05/15 20:56:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;

	(void)ac;
	(void)av;

	while ("this is the best minishell")
	{
		input = display_prompt();
		if(ft_strlen(input)> 0)
		{
			input_tab = ft_split(input, ' ');
			isbuiltin(input_tab, env);
			//lexer
			//parser
			//built-in
			//pipe
			//redirections
			//execution
			//expand
		}
		free(input);
	}
}
