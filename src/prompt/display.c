/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:57:37 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/12 23:16:05 by madlab           ###   ########.fr       */
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
		return (free(tmp), NULL);
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
		return (NULL);
	if (input && *input)
		add_history(input);
	return (input);
}
