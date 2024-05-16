/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:46:40 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/15 02:26:07 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*input;
	(void)ac;
	(void)av;
	(void)env;
	while ("this is the best minishell")
	{
		input = display_prompt();
		//cd(input);
		//ft_env(env);
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
