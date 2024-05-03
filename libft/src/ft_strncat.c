/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 10:12:12 by dbaladro          #+#    #+#             */
/*   Updated: 2024/02/03 12:19:02 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	unsigned int	i;
	char			*dest_cp;

	dest_cp = dest;
	i = 0;
	while (*dest_cp)
		dest_cp++;
	while (src[i] && i < nb)
	{
		dest_cp[i] = src[i];
		i++;
	}
	dest_cp[i] = '\0';
	return (dest);
}
