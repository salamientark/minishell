/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:38:06 by dbaladro          #+#    #+#             */
/*   Updated: 2024/06/03 19:38:14 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/* Make here_doc filename based on couunt (+ maybe shlvl in the future)
 * */
char	*here_doc_name(char buff_name[11], int here_doc_count)
{
	buff_name[0] = '/';
	buff_name[1] = 't';
	buff_name[2] = 'm';
	buff_name[3] = 'p';
	buff_name[4] = '/';
	buff_name[5] = '.';
	buff_name[6] = '0';
	buff_name[7] = '0';
	buff_name[8] = '0';
	buff_name[9] = (here_doc_count / 10) + '0';
	buff_name[10] = (here_doc_count % 10) + '0';
	buff_name[11] = '\0';
	return (buff_name);
}
