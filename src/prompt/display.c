/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:57:37 by ple-guya          #+#    #+#             */
/*   Updated: 2024/06/17 16:28:44 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*interactiveprompt(void)
// {
// 	char	*input;
// 	char	*prompt;
// 	char	*tmp;
// 	char	pwd[MAX_PATHLEN];
// 
// 	getcwd(pwd, MAX_PATHLEN);
// 	tmp = ft_strjoin("\001\033[0;35m\002>", pwd);
// 	if (!tmp)
// 		return (NULL);
// 	prompt = ft_strjoin(tmp, "\001\033[0;37m$\002 ");
// 	if (!prompt)
// 		return (free(tmp), NULL);
// 	free(tmp);
// 	input = readline(prompt);
// 	free(prompt);
// 	return (input);
// }

static void	update_prompt_exit_status(t_chill *shell)
{
	int	index;

	index = 0;
	while (shell->prompt[index] != '\0')
		index++;
	index -= 16;
	if (shell->exit_status == 0)
		shell->prompt[index] = '2';
	else
		shell->prompt[index] = '1';
}

char	*read_command(t_chill *shell)
{
	char	*input;

	update_prompt_exit_status(shell);
	input = readline(shell->prompt);
	rl_on_new_line();
	if (!input)
	{
		ft_putendl_fd("exit", 1);
		exit(0);
	}
	if (input && *input)
		add_history(input);
	return (input);
}
