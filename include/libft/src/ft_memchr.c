/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:47:15 by tlize             #+#    #+#             */
/*   Updated: 2025/04/13 15:14:48 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char		*s_char;
	size_t		i;

	i = 0;
	s_char = (char *)s;
	while (i < n)
	{
		if ((unsigned char)s_char[i] == (unsigned char)c)
			return ((char *)s + i);
		i ++;
	}
	return (NULL);
}
