/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:03:20 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/13 11:59:01 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_words(const char *str)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (is_whitespace(*str))
			in_word = 0;
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

static char	*extract_word(const char *start, int len)
{
	char	*word;
	int		i;

	word = malloc(len + 1);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	skip_whitespace(char *input, int *i)
{
	while (input[*i] && is_whitespace(input[*i]))
		(*i)++;
}

static int	fill_words(char **words, char *input)
{
	int	i;
	int	start;
	int	word_len;
	int	w;

	i = 0;
	w = 0;
	while (input[i])
	{
		skip_whitespace(input, &i);
		start = i;
		while (input[i] && !is_whitespace(input[i]))
			i++;
		word_len = i - start;
		if (word_len > 0)
		{
			words[w] = extract_word(&input[start], word_len);
			if (!words[w])
				return (0);
			w++;
		}
	}
	words[w] = NULL;
	return (1);
}

t_token	tokenize_line(char *input)
{
	t_token	token;
	int		success;

	token.count = count_words(input);
	token.words = malloc(sizeof(char *) * (token.count + 1));
	if (!token.words)
	{
		token.count = 0;
		return (token);
	}
	success = fill_words(token.words, input);
	if (!success)
	{
		token.count = 0;
		free(token.words);
		token.words = NULL;
	}
	return (token);
}
