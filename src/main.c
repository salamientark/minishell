/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:46:40 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/14 18:24:57 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main()
{
	char *input;
	char **cmd;
	
	while ("this is the best minishell")
	{
		input = display_prompt();
		cd(input);
		if (!ft_strcmp(input, "ls"))
			execve("/bin/ls", cmd, env);
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
