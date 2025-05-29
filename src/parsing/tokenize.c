/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:39:55 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/29 17:43:57 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**alloc_tokens_array(int count)
{
	char **tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	return (tokens);
}

static int	handle_token(const char *str, int *i, char **tokens, int idx)
{
	int	start = *i;
	int	end;

	if (str[*i] == '\'' || str[*i] == '"')
		end = extract_quoted_token(str, *i, str[*i]);
	else
		end = extract_token(str, *i);
	if (end < start)
		return (0);
	tokens[idx] = copy_token(str, start, end);
	if (!tokens[idx])
		return (0);
	*i = (str[end]) ? end + 1 : end;
	return (1);
}

static char	**tokenize_loop(const char *str, char **tokens)
{
	int	i = 0;
	int	idx = 0;
	int	count = count_tokens(str);

	tokens = alloc_tokens_array(count);
	if (!tokens)
		return (NULL);
	while (str[i])
	{
		i = skip_spaces(str, i);
		if (!str[i])
			break ;
		if (!handle_token(str, &i, tokens, idx))
		{
			free_tokens(tokens);
			return (NULL);
		}
		idx++;
	}
	tokens[idx] = NULL;
	return (tokens);
}

char	**tokenize_simple(const char *str)
{
	return (tokenize_loop(str, NULL));
}
