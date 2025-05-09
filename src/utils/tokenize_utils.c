/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:38:08 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/09 15:39:52 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*extract_word(const char *start, int len)
{
	char	*word;

	word = malloc(len + 1);
	if (!word)
		return (NULL);
	strncpy(word, start, len);
	word[len] = '\0';
	return (word);
}

void	advance_to_word_end(const char *input, int *i)
{
	while (input[*i] && !is_whitespace(input[*i]))
		(*i)++;
}

void	process_quoted_word(const char *input, int *i, int *start, int *len)
{
	char	quote_char;

	quote_char = input[(*i)++];
	*start = *i;
	while (input[*i] && input[*i] != quote_char)
		(*i)++;
	*len = *i - *start;
	if (input[*i] == quote_char)
		(*i)++;
}

void	process_normal_word(const char *input, int *i, int *start, int *len)
{
	*start = *i;
	advance_to_word_end(input, i);
	*len = *i - *start;
}
