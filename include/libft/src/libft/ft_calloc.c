/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 14:39:05 by tlize             #+#    #+#             */
/*   Updated: 2025/04/13 15:14:24 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*pt;

	if (nmemb > __SIZE_MAX__ / size)
		return (0);
	if (nmemb < 1 && size < 1)
	{
		nmemb = 1;
		size = 1;
	}
	pt = malloc(nmemb * size);
	if (!pt)
		return (pt);
	ft_bzero(pt, (nmemb * size));
	return (pt);
}
