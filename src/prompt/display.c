/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:57:37 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/11 20:48:39 by ple-guya         ###   ########.fr       */
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
		return (NULL);
	prompt = ft_strjoin(tmp, "\001\033[0;37m$\002 ");
	if (!prompt)
		return (NULL);
	free(tmp);
	input = readline(prompt);
	free(prompt);
	return (input);
}

char	*display_prompt(void)
{
	char	*input;

	input = interactiveprompt();
	rl_on_new_line();
	if (!input)
	{
		free(input);
		rl_clear_history();
		write(1, "exit\n", 5);
		exit(0);
	}
	if (input && *input)
		add_history(input);
	return (input);
}
