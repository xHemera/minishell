/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:45:34 by marvin            #+#    #+#             */
/*   Updated: 2025/07/24 21:45:34 by marvin           ###   ########.fr       */
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

static int	should_expand_variable(char *str, int i)
{
	return (str[i] == '$' && str[i + 1]
		&& (ft_isalnum(str[i + 1]) || str[i + 1] == '_'
			|| str[i + 1] == '?' || str[i + 1] == '$'));
}

char	*ft_expand_variables_quotes(char *str, t_env *env, int last_exit_code)
{
	int		i;
	char	*temp_str;
	char	quote;

	if (!str)
		return (NULL);
	temp_str = ft_strdup(str);
	if (!temp_str)
		return (NULL);
	i = 0;
	while (temp_str[i])
	{
		if (should_expand_variable(temp_str, i))
		{
			quote = get_current_quote(temp_str, i);
			if (quote == '\'')
				i++;
			else
				temp_str = expand_single_variable(temp_str, &i, env,
						last_exit_code);
		}
		else
			i++;
	}
	return (temp_str);
}
