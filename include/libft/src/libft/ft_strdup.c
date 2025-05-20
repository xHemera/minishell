/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:57:51 by tlize             #+#    #+#             */
/*   Updated: 2025/04/13 15:15:20 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strcopy(char *str, char *copy)
{
	int	i;

	i = 0;
	while (str[i])
	{
		copy[i] = str[i];
		i ++;
	}
	copy[i] = '\0';
}

char	*ft_strdup(const char *s)
{
	char	*copy;
	char	*str;

	str = (char *)s;
	copy = (char *) malloc((ft_strlen(str) + 1) * sizeof(char));
	if (copy == NULL)
		return (NULL);
	ft_strcopy(str, copy);
	return (copy);
}
