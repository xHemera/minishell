/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_improved.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:46:40 by marvin            #+#    #+#             */
/*   Updated: 2025/07/24 21:46:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_token(const char *str, char **tokens, int *i, int token_idx)
{
	int	end;

	if (str[*i] == '<' || str[*i] == '>' || str[*i] == '|')
	{
		if (!handle_operator_token(str, tokens, i, token_idx))
			return (0);
	}
	else
	{
		tokens[token_idx] = extract_full_token(str, *i, &end);
		if (!tokens[token_idx])
			return (0);
		*i = end;
	}
	return (1);
}

char	**tokenize_improved(const char *str)
{
	char	**tokens;
	int		count;
	int		i;
	int		token_idx;

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
			break ;
		if (!process_token(str, tokens, &i, token_idx))
		{
			free_tokens(tokens);
			return (NULL);
		}
		token_idx++;
	}
	tokens[token_idx] = NULL;
	return (tokens);
}
