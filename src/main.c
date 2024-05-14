/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:46:40 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/14 14:18:09 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../src/test/test.h"

int	main(int ac, char **av)
{
	(void) ac;
	(void) av;
	char	*line;
	char	**input_tab;

	write(1, "$ ", 2);
	line = get_next_line(0);
	while (line)
	{
		input_tab = split_input(line);
		if (input_tab)
			return (free(line), 1);
		print_input(input_tab);
	// 	printf("Does < %s\tContain unclosed quote or bracket ? : %d\n", line,
	// 			unclosed_quote_bracket(line));
		free(line);
		write(1, "$ ", 2);
		line = get_next_line(0);
	}
	return (0);
}
