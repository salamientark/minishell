/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:57:37 by ple-guya          #+#    #+#             */
/*   Updated: 2024/05/08 21:28:31 by ple-guya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/includes/libft.h"
#include <stdio.h>
#include <stdlib.h>

#include<readline/readline.h>
#include<readline/history.h>
#include "test.h"

int	main(int argc, char** argv)
{
	char	*input;
	char	*cpy;
	char	*pwd;

	while (1)
	{
		input = readline("\033[0;35mminitest\033[0;37m ");
		if (input && *input)
			add_history(input);
		while (*input == ' ')
			input++;
		if (!ft_strlen(input))
		{
			free(input);
			continue;
		}
		if (!input || !ft_strncmp(input, "exit", ft_strlen(input)))
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		write(1, input, 8);
		write(1, "\n", 1);
	}
	return 0;
}
