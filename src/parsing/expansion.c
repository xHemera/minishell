/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:45:42 by marvin            #+#    #+#             */
/*   Updated: 2025/07/24 21:45:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_single_variable(char *temp_str, int *i, t_env *env,
		int last_exit_code)
{
	char	*var_name;
	char	*value;
	char	*str;
	int		end;

	var_name = ft_extract_var_name(temp_str, *i + 1);
	end = ft_find_var_end(temp_str, *i + 1);
	value = ft_get_var_value(var_name, env, last_exit_code);
	str = temp_str;
	temp_str = ft_replace_variable(temp_str, *i, *i + 1 + (end - (*i + 1)),
			value);
	free(str);
	free(var_name);
	*i += ft_strlen(value);
	free(value);
	return (temp_str);
}

char	*ft_expand_variables(char *str, t_env *env, int last_exit_code)
{
	int		i;
	char	*temp_str;

	if (!str)
		return (NULL);
	temp_str = ft_strdup(str);
	if (!temp_str)
		return (NULL);
	i = 0;
	while (temp_str[i])
	{
		if (temp_str[i] == '$' && temp_str[i + 1]
			&& (ft_isalnum(temp_str[i + 1]) || temp_str[i + 1] == '_'
				|| temp_str[i + 1] == '?' || temp_str[i + 1] == '$'))
		{
			temp_str = expand_single_variable(temp_str, &i, env,
					last_exit_code);
		}
		else
			i++;
	}
	return (temp_str);
}
