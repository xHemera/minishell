/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 16:50:53 by tlize             #+#    #+#             */
/*   Updated: 2025/04/13 16:48:58 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ftt_strlen(const char *str)
{
	size_t	i;
	char	*str_char;

	i = 0;
	str_char = (char *)str;
	while (str_char[i])
		i ++;
	return (i);
}

char	*ftt_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if ((char)c == '\0')
		return ((char *)s + ftt_strlen(s));
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i ++;
	}
	return (0);
}

char	*ftt_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (ftt_strlen(s1) + ftt_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i ++;
	}
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j ++;
	}
	str[i + j] = '\0';
	return (str);
}

static void	*ftt_memset(void *s, int c, size_t n)
{
	char	*s_char;

	s_char = (char *)s;
	while (n > 0)
	{
		s_char[n - 1] = c;
		n--;
	}
	return (s);
}

void	*ftt_calloc(size_t nmemb, size_t size)
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
	ftt_memset(pt, '\0', (nmemb * size));
	return (pt);
}
