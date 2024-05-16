/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:57:37 by ple-guya          #+#    #+#             */
/*   Updated: 2024/05/16 15:52:22 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*interactiveprompt()
{
	char	*input;
	char	*prompt;
	char	pwd[MAX_PATHLEN];

	getcwd(pwd, MAX_PATHLEN);
	prompt = ft_strjoin("\001\033[0;35m\002", pwd);
	prompt = ft_strjoin(prompt, "\001\033[0;37m$\002 ");
	input = readline(prompt);
	free(prompt);
	return(input);
}

char	*display_prompt(void)
{
	char	*input;
	
	input = interactiveprompt();
	if (!input)
	{
		free(input);
		write(1, "exit\n", 5);
		exit(0);
	}
	if (input && *input)
		add_history(input);
	return (input);
}
