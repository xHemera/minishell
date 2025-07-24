/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_var_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:45:39 by marvin            #+#    #+#             */
/*   Updated: 2025/07/24 21:45:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_var_value(char *var_name, t_env *env, int last_exit_code)
{
	if (!var_name)
		return (NULL);
	if (ft_strncmp(var_name, "?", 2) == 0)
		return (ft_itoa(last_exit_code));
	if (ft_strncmp(var_name, "$", 2) == 0)
		return (ft_itoa(getpid()));
	while (env)
	{
		if (ft_strncmp(env->key, var_name, ft_strlen(var_name) + 1) == 0)
		{
			if (env->value)
				return (ft_strdup(env->value));
			return (ft_strdup(""));
		}
		env = env->next;
	}
	return (ft_strdup(""));
}

char	*ft_extract_var_name(char *str, int start)
{
	int		end;
	char	*var_name;
	int		len;

	end = ft_find_var_end(str, start);
	len = end - start;
	var_name = malloc(len + 1);
	if (!var_name)
		return (NULL);
	ft_memcpy(var_name, str + start, len);
	var_name[len] = '\0';
	return (var_name);
}

int	ft_find_var_end(char *str, int start)
{
	int	i;

	i = start;
	if (str[i] == '?' || str[i] == '$')
		return (i + 1);
	while (str[i] && ft_is_valid_var_char(str[i], i == start))
		i++;
	return (i);
}

int	ft_is_valid_var_char(char c, int first)
{
	if (first)
		return (ft_isalpha(c) || c == '_');
	return (ft_isalnum(c) || c == '_');
}
