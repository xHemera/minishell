/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_improved_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:46:38 by marvin            #+#    #+#             */
/*   Updated: 2025/07/24 21:46:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_token_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '<' || c == '>' || c == '|');
}

int	handle_operator_token(const char *str, char **tokens,
	int *i, int token_idx)
{
	char	*token;

	if (str[*i + 1] && ((str[*i] == '<' && str[*i + 1] == '<')
			|| (str[*i] == '>' && str[*i + 1] == '>')))
	{
		token = malloc(3);
		if (!token)
			return (0);
		token[0] = str[*i];
		token[1] = str[*i + 1];
		token[2] = '\0';
		*i += 2;
	}
	else
	{
		token = malloc(2);
		if (!token)
			return (0);
		token[0] = str[*i];
		token[1] = '\0';
		(*i)++;
	}
	tokens[token_idx] = token;
	return (1);
}

static int	find_token_end(const char *str, int start)
{
	int	i;

	i = start;
	while (str[i] && !is_token_separator(str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
			handle_quote_section(str, &i, str[i]);
		else
			i++;
	}
	return (i);
}

char	*extract_full_token(const char *str, int start, int *end)
{
	char	*result;
	int		len;

	*end = find_token_end(str, start);
	len = *end - start;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, str + start, len);
	result[len] = '\0';
	return (result);
}
