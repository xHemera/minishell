/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 16:41:56 by tlize             #+#    #+#             */
/*   Updated: 2025/04/13 16:42:09 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, int n)
{
	int	val;

	val = 0;
	while (val < n && src[val] != '\0')
	{
		dest[val] = src[val];
		val++;
	}
	while (val < n)
	{
		dest[val] = '\0';
		val++;
	}
	return (dest);
}
