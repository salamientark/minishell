/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:46:40 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/14 15:19:11 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	char *input;
	
	while ("this is the best minishell")
	{
		input = display_prompt();
		//lexer
		//parser
		//built-in
		//pipe
		//redirections
		//execution
		//expand
		free(input);
	}
}
