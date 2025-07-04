/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:01:00 by tobesnar          #+#    #+#             */
/*   Updated: 2025/07/04 16:01:00 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_unclosed_quotes(const char *str)
{
	int		i;
	char	quote;
	int		in_quote;

	i = 0;
	in_quote = 0;
	quote = 0;
	while (str[i])
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
	return (in_quote);
}

char	*remove_quotes(char *str)
{
	int		i;
	int		j;
	char	*result;
	char	quote;
	int		in_quote;

	if (!str)
		return (NULL);
	result = malloc(ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_quote = 0;
	quote = 0;
	while (str[i])
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
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

int	should_expand_in_quotes(char quote_type)
{
	return (quote_type == '"' || quote_type == 0);
}
