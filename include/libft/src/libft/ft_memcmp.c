/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:05:23 by tlize             #+#    #+#             */
/*   Updated: 2025/04/13 15:14:51 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	char		*s1_char;
	char		*s2_char;
	size_t		i;

	i = 0;
	s1_char = (char *)s1;
	s2_char = (char *)s2;
	while (i < n)
	{
		if (s1_char[i] != s2_char[i])
			return ((unsigned char)s1_char[i] - (unsigned char)s2_char[i]);
		i ++;
	}
	return (0);
}
