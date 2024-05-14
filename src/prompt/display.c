/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:57:37 by ple-guya          #+#    #+#             */
/*   Updated: 2024/05/14 17:02:11 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void	check_exit(char *input)
{
	char	*cpy;

	if (!input)
	{
		free(input);
		write(1, "exit\n", 5);
		exit(0);
	}
	cpy = input;
	while (*cpy == ' ')
		cpy++;
	if ((!ft_strcmp(cpy, "exit")))
	{
		free(input);
		write(1, "exit\n", 5);
		exit(0);
	}
}

static char	*interactiveprompt()
{
	char	*input;
	char	*prompt;
	char	pwd[100];

	getcwd(pwd, 100);
	prompt = ft_strjoin("\033[0;35m", pwd);
	prompt = ft_strjoin(prompt, "\033[0;37m$ ");
	input = readline(prompt);
	free(prompt);
	return(input);
}

char	*display_prompt(void)
{
	char	*input;
	
	input = interactiveprompt();
	check_exit(input);
	if (input && *input)
		add_history(input);
	return (input);
}
