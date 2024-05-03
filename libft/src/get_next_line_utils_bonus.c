/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:38:04 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/28 07:16:24 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line_bonus.h"

// Free_all the block and content from text_block to end of it
void	free_buffer(t_block **text_block)
{
	t_block	*tmp;

	while ((*text_block))
	{
		tmp = (*text_block)->next;
		free((*text_block)->content);
		(*text_block)->content = NULL;
		free((*text_block));
		(*text_block) = NULL;
		(*text_block) = tmp;
	}
}

// Free and remove the associated fd_env if found
void	del_fd_env(t_fd_env **gnl_env, const int fd)
{
	t_fd_env	*record;
	t_fd_env	*tmp;

	tmp = (*gnl_env)->next;
	if (tmp == NULL || (*gnl_env)->fd == fd)
	{
		if ((*gnl_env)->buffer)
			free_buffer(&((*gnl_env)->buffer));
		free((*gnl_env));
		((*gnl_env)) = tmp;
		return ;
	}
	record = (*gnl_env);
	while (record->next)
	{
		if (record->next->fd == fd)
		{
			tmp = record->next->next;
			free_buffer(&(record->next->buffer));
			free(record->next);
			record->next = tmp;
			return ;
		}
		record = record->next;
	}
}

// Init an empty text_block
//	Return :
//		t_block * : Empty block
t_block	*init_block(void)
{
	t_block	*block;

	block = (t_block *)malloc(sizeof(struct s_block));
	if (!block)
		return (NULL);
	block->content = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!block->content)
	{
		free(block);
		return (NULL);
	}
	block->content_len = 0;
	block->last_pos = 0;
	block->next = NULL;
	return (block);
}

// Init gnl_env with associated fd and allocated buffer
//	Return :
//		t_fd_env * : Empty gnl_env
//		NULL		: error
t_fd_env	*init_fd_env(const int fd)
{
	t_fd_env	*gnl_env;

	gnl_env = (t_fd_env *)malloc(sizeof(t_fd_env));
	if (!gnl_env)
		return (NULL);
	gnl_env->buffer = init_block();
	if (!gnl_env->buffer)
	{
		free(gnl_env);
		return (NULL);
	}
	gnl_env->next = NULL;
	gnl_env->fd = fd;
	return (gnl_env);
}

// Move block->buffer_content at the beginning of it
// after a line was read
//		Return :
//			void
void	content_move(t_block **block)
{
	int	index;

	index = 0;
	(*block)->last_pos = (*block)->last_pos + 1;
	while (index < ((*block)->content_len - (*block)->last_pos)
		&& (*block)->content[(*block)->last_pos + index] != '\0')
	{
		(*block)->content[index] = (*block)->content[(*block)->last_pos
			+ index];
		index++;
	}
	(*block)->content_len = index;
	(*block)->last_pos = 0;
	while ((*block)->last_pos < (*block)->content_len
		&& (*block)->content[(*block)->last_pos] != '\n')
		(*block)->last_pos = (*block)->last_pos + 1;
}
