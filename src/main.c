/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:46:40 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/15 18:18:23 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	main()
{
	char	*input;

	while ("this is the best minishell")
	{
		input = display_prompt();
		// 		write(1, input, 4);
// 		write(1, "\n", 1);
		if (ft_strlen(input) > 0)
		{
			if (!unclosed_delimiter(input))
				printf("input is WELL CLOSED\n");

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
