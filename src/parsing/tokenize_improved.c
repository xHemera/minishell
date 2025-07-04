/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_improved.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:12:00 by tobesnar          #+#    #+#             */
/*   Updated: 2025/07/04 16:12:00 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_token_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '<' || c == '>' || c == '|');
}

static int	count_tokens_improved(const char *str)
{
	int	i;
	int	count;
	int	in_token;

	i = 0;
	count = 0;
	in_token = 0;
	while (str[i])
	{
		if (is_token_separator(str[i]) && str[i] != '\'' && str[i] != '"')
		{
			if (in_token)
			{
				count++;
				in_token = 0;
			}
			if (str[i] == '<' || str[i] == '>' || str[i] == '|')
			{
				count++;
				if (str[i + 1] && ((str[i] == '<' && str[i + 1] == '<') ||
					(str[i] == '>' && str[i + 1] == '>')))
					i++;
			}
		}
		else if (!is_token_separator(str[i]) || str[i] == '\'' || str[i] == '"')
		{
			if (!in_token)
				in_token = 1;
			if (str[i] == '\'' || str[i] == '"')
			{
				char quote = str[i];
				i++;
				while (str[i] && str[i] != quote)
					i++;
			}
		}
		i++;
	}
	if (in_token)
		count++;
	return (count);
}

static char	*extract_full_token(const char *str, int start, int *end)
{
	int		i;
	char	*result;
	int		len;

	i = start;
	while (str[i] && !is_token_separator(str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			char quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
			if (str[i])
				i++;
		}
		else
			i++;
	}
	*end = i;
	len = i - start;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, str + start, len);
	result[len] = '\0';
	return (result);
}

char	**tokenize_improved(const char *str)
{
	char	**tokens;
	int		count;
	int		i;
	int		token_idx;
	int		end;

	count = count_tokens_improved(str);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	token_idx = 0;
	while (str[i] && token_idx < count)
	{
		i = skip_spaces(str, i);
		if (!str[i])
			break;
		if (str[i] == '<' || str[i] == '>' || str[i] == '|')
		{
			if ((str[i] == '<' && str[i + 1] == '<') ||
				(str[i] == '>' && str[i + 1] == '>'))
			{
				tokens[token_idx] = malloc(3);
				if (!tokens[token_idx])
					return (NULL);
				tokens[token_idx][0] = str[i];
				tokens[token_idx][1] = str[i + 1];
				tokens[token_idx][2] = '\0';
				i += 2;
			}
			else
			{
				tokens[token_idx] = malloc(2);
				if (!tokens[token_idx])
					return (NULL);
				tokens[token_idx][0] = str[i];
				tokens[token_idx][1] = '\0';
				i++;
			}
		}
		else
		{
			tokens[token_idx] = extract_full_token(str, i, &end);
			if (!tokens[token_idx])
				return (NULL);
			i = end;
		}
		token_idx++;
	}
	tokens[token_idx] = NULL;
	return (tokens);
}
