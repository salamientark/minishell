/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 10:43:15 by madlab            #+#    #+#             */
/*   Updated: 2024/06/13 10:43:55 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

/* Delete all here_doc file
 * */
void	unlink_here_doc(void)
{
	unlink("/tmp/.00000");
	unlink("/tmp/.00001");
	unlink("/tmp/.00002");
	unlink("/tmp/.00003");
	unlink("/tmp/.00004");
	unlink("/tmp/.00005");
	unlink("/tmp/.00006");
	unlink("/tmp/.00007");
	unlink("/tmp/.00008");
	unlink("/tmp/.00009");
	unlink("/tmp/.00010");
	unlink("/tmp/.00011");
	unlink("/tmp/.00012");
	unlink("/tmp/.00013");
	unlink("/tmp/.00014");
	unlink("/tmp/.00015");
}
