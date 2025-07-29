/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:32:04 by tobesnar          #+#    #+#             */
/*   Updated: 2025/07/29 10:32:04 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*allocate_new_str(char *str, int start, int end, char *value)
{
	int		new_len;
	char	*new_str;

	new_len = ft_strlen(str) - (end - start) + ft_strlen(value);
	new_str = malloc(new_len + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, str, start);
	ft_memcpy(new_str + start, value, ft_strlen(value));
	ft_memcpy(new_str + start + ft_strlen(value),
		str + end, ft_strlen(str) - end);
	new_str[new_len] = '\0';
	return (new_str);
}

char	*ft_replace_variable(char *str, int start, int end, char *value)
{
	char	*new_str;

	if (!str || !value)
		return (NULL);
	new_str = allocate_new_str(str, start, end, value);
	return (new_str);
}
