/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:57:37 by ple-guya          #+#    #+#             */
/*   Updated: 2024/05/14 22:00:43 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

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
	prompt = ft_strjoin("\001\033[0;35m\002", pwd);
	prompt = ft_strjoin(prompt, "\001\033[0;37m\002$ ");
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
	if (ft_strlen(input) > 0)
		printf("\n");
	return (input);
}
