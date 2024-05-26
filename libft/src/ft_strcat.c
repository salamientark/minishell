/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ple-guya <ple-guya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:59:15 by dbaladro          #+#    #+#             */
/*   Updated: 2024/05/24 16:20:55 by madlab           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *dest, char *src)
{
	char	*dest_cp;
	int		i;

	if (!src || !(*src))
		return (dest);
	dest_cp = dest;
	while (*dest_cp)
		dest_cp++;
	i = 0;
	while (src[i])
	{
		dest_cp[i] = src[i];
		i++;
	}
	dest_cp[i] = '\0';
	return (dest);
}
