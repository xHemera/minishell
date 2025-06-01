/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:39:55 by tobesnar          #+#    #+#             */
/*   Updated: 2025/06/01 14:22:34 by hemera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**alloc_tokens_array(int count)
{
	char	**tokens;

	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	return (tokens);
}

static int	handle_token(const char *str, int *i, char **tokens, int idx)
{
	int	start;
	int	end;

	start = *i;
	if (str[*i] == '\'' || str[*i] == '"')
		end = extract_quoted_token(str, *i, str[*i]);
	else
		end = extract_token(str, *i);
	if (end < start)
		return (0);
	tokens[idx] = copy_token(str, start, end);
	if (!tokens[idx])
		return (0);
	if (str[end])
		*i = end + 1;
	else
		*i = end;
	return (1);
}

static int	init_tokenize_loop_vars(const char *str,
	int *i, int *idx, int *count)
{
	*i = 0;
	*idx = 0;
	*count = count_tokens(str);
	if (*count < 0)
		return (0);
	return (1);
}

static char	**tokenize_loop(const char *str, char **tokens)
{
	int	i;
	int	idx;
	int	count;

	if (!init_tokenize_loop_vars(str, &i, &idx, &count))
		return (NULL);
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
