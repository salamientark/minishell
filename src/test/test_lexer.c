/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:09:32 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/14 19:15:41 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/test.h"

void	print_input(char **input_tab)
{
	int	index;

	index = 0;
	while (input_tab[index])
	{
		printf("%s\n", input_tab[index]);
		index++;
	}
}
