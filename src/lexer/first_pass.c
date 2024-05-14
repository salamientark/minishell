/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_pass.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madlab <madlab@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 22:40:05 by madlab            #+#    #+#             */
/*   Updated: 2024/05/14 14:08:08 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * THE FIRST PASS HAPPEN AFTER THE QUOTE/BRACE CHECK
 * IT'S THE 'syntax error' checker + here_doc executor:
 *	The syntax error happen if you try to pipe/redirect from/to nothing
 *	$ | ls					=> SYNTAX ERROR
 *	$ ls |					=> SYNTAX ERROR
 *	$ <						=> SYNTAX ERROR
 *	$ ls | cat <<			=> SYNTAX ERROR
 *	$ ls | cat << LIM | <	=> HERE_DOC then SYNTAX_ERROR
 * THe first pass will open here_doc and check for syntax error
 *	IN THE ORDER THEY APPEAR
 *	*/

#include "../../includes/minishell.h"

int	is_preceeded_by_word(const char *cmd, int index)
{
	while (index >= 0 && (cmd[index] == SPACE || cmd[index] == TAB))
		index--;
	if (index == -1 || cmd[index] == '\n')
		return (1);
	if (!is_operator(cmd[index]))
		return (0);
	return (1);
}

int	is_followed_by_word(const char *cmd, int index)
{
	index++;
	while (cmd[index] && (cmd[index] == SPACE || cmd[index] == TAB))
		index++;
	if (!cmd[index] || cmd[index] == '\n')
		return (1);
	if (!is_operator(cmd[index]))
		return (0);
	return (1);
}

void	get_operator(const char *cmd, char buff[], int index)
{
	buff[0] = cmd[index];
	buff[1] = 0;
	buff[2] = 0;
	if (!(cmd[index] == LESS_THAN || cmd[index] == GREATER_THAN
				|| cmd[index] == PIPE || cmd[index] == AMPERSAND))
		return ;
	if (cmd[index + 1] && cmd[index + 1] == cmd[index])
		buff[1] = cmd[index + 1];
	return ;
}

/*
 * If operator == |, ||, &&, ) without previous (
 * Check if previous token is operator.
 * If yes -> Syntax error
 * 
 * If operator == <, <<, >, >>
 * Check if next token is operator
 * if yes return -> sytax error
 * 
 * ||, &&, (, | with nothing after should be detected before
 * (unclosed quote/brace pass)
 * */
int	first_pass(const char *cmd)
{
	int		index;
	char	last_quote;
	char	buffer[3];

	if (!cmd)
		return (0);
	index = 0;
	while (cmd[index])
	{
		if (is_operator(cmd[index]))
		{
			get_operator(cmd, buffer, index);
			if (is_control_operator(buffer[0]))
			{
				if (!(is_preceeded_by_word(cmd, index)))
					return (syntax_error(buffer), 1);
				index = index + 1 + (buffer[1] != 0);
			}
			else
				// REDIRECTION_OPERATOR -> CCHECK NEXT WORD
			{
				index = index + (buffer[1] != 0);
				if (!(is_followed_by_word(cmd, index)))
					// ERROR
				index = index + 1 + (buffer[1] != 0);
			}
			buffer[1] = 0;
		}
		if (cmd[index] == DOUBLE_QUOTE || cmd[index] == SINGLE_QUOTE
				|| cmd[index] == LEFT_BRACE)
		{
			last_quote = cmd[index++];
			while (cmd[index] != last_quote)
				index++;
			index++;
		}
		index++;
	}
	return (0);
}

int	first_pass(const char *cmd)
{
	int	index;

	if (!cmd)
		return (0);
	index = 0;
	while (cmd[index])
	{
		if (cmd[index] == PIPE) // PIPE
			// CHECK PREVIOUS CHAR IF IT WEAS OPERATOR -> SYBNTAX ERROR
			// ALSO CHECK IF NEXT WORD IS A word
			//  It may be done by just cheking if previous char
			//  (skipping space and tabs) is not an operator
			//  (letter, number, quotes...) are not operator and acceptable 
		if (cmd[index] == LESS_THAN) // HERE_DOC or REDIRECT_FROM
		{
			index++;
			if (cmd[index] == LESS_THAN) // HERE_DOC
			{
				// CHEK IF LIMITER
				// OPEN HERE_DOC
			}
			else
			{
				// CHECK IF NEXT WORD IS A word
			}
		}
		if (cmd[index] == GREATER_THAN) // REDIRECT TO
		{
			// SKIP OTHER GREATER THAN IF APPEND MODE 
			// THEN CHECK IF NEXT WORD IS A word
		}
		index++;
	}
}
