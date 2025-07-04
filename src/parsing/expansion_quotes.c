/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:01:00 by tobesnar          #+#    #+#             */
/*   Updated: 2025/07/04 16:01:00 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	get_current_quote(char *str, int pos)
{
	int		i;
	char	quote;
	int		in_quote;

	i = 0;
	in_quote = 0;
	quote = 0;
	while (i < pos && str[i])
	{
		if (!in_quote && (str[i] == '\'' || str[i] == '"'))
		{
			in_quote = 1;
			quote = str[i];
		}
		else if (in_quote && str[i] == quote)
		{
			in_quote = 0;
			quote = 0;
		}
		i++;
	}
	return (quote);
}

char	*ft_expand_variables_quotes(char *str, t_env *env, int last_exit_code)
{
	int		i;
	char	*var_name;
	char	*value;
	char	*temp_str;
	int		end;
	char	quote;

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
			quote = get_current_quote(temp_str, i);
			if (quote == '\'')
			{
				i++;
				continue;
			}
			var_name = ft_extract_var_name(temp_str, i + 1);
			end = ft_find_var_end(temp_str, i + 1);
			value = ft_get_var_value(var_name, env, last_exit_code);
			str = temp_str;
			temp_str = ft_replace_variable(temp_str, i, i + 1 + (end - (i + 1)), value);
			free(str);
			free(var_name);
			i += ft_strlen(value);
			free(value);
		}
		else
			i++;
	}
	return (temp_str);
}
