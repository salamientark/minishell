/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:46:40 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/08 17:11:39 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av)
{
	(void) ac;
	(void) av;
	char *line;

	write(1, "$ ", 2);
	line = get_next_line(0);
	while (line)
	{
		printf("Does < %s\tContain unclosed quote or bracket ? : %d\n", line,
				unclosed_quote_bracket(line));
		free(line);
		write(1, "$ ", 2);
		line = get_next_line(0);
	}
	return (0);
}
