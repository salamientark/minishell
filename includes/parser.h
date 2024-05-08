/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 15:08:26 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/08 17:11:59 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define DOUBLE_QUOTE '\"' 
# define SINGLE_QUOTE '\'' 
# define LEFT_BRACE '{'
# define RIGHT_BRACE '}'
# define DOLLAR '$'

int	unclosed_quote(const char *cmd);
int	unclosed_quote_bracket(const char *input);

#endif
