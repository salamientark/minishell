/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:57:37 by ple-guya          #+#    #+#             */
/*   Updated: 2024/05/16 21:50:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*interactiveprompt(void)
{
	char	*input;
	char	*prompt;
	char	*tmp;
	char	pwd[MAX_PATHLEN];

	getcwd(pwd, MAX_PATHLEN);
	tmp = ft_strjoin("\001\033[0;35m\002>", pwd);
	if (!tmp)
		return(NULL);
	prompt = ft_strjoin(tmp, "\001\033[0;37m$\002 ");
	if (!prompt)
		return(NULL);
	free(tmp);
	input = readline(prompt);
	free(prompt);
	return (input);
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
