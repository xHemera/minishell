/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_quote_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:46:42 by marvin            #+#    #+#             */
/*   Updated: 2025/07/24 21:46:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quote_section(const char *str, int *i, char quote)
{
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i])
		(*i)++;
}

void	handle_token_separator(const char *str, int *i, int *count,
	int *in_token)
{
	if (is_token_separator(str[*i]) && str[*i] != '\'' && str[*i] != '"')
	{
		if (*in_token)
		{
			(*count)++;
			*in_token = 0;
		}
		if (str[*i] == '<' || str[*i] == '>' || str[*i] == '|')
		{
			(*count)++;
			if (str[*i + 1] && ((str[*i] == '<' && str[*i + 1] == '<')
					|| (str[*i] == '>' && str[*i + 1] == '>')))
				(*i)++;
		}
	}
	else if (!is_token_separator(str[*i]) || str[*i] == '\'' || str[*i] == '"')
	{
		if (!*in_token)
			*in_token = 1;
		if (str[*i] == '\'' || str[*i] == '"')
			handle_quote_section(str, i, str[*i]);
	}
}

int	count_tokens_improved(const char *str)
{
	int	i;
	int	count;
	int	in_token;

	i = 0;
	count = 0;
	in_token = 0;
	while (str[i])
	{
		handle_token_separator(str, &i, &count, &in_token);
		if (str[i])
			i++;
	}
	if (in_token)
		count++;
	return (count);
}
