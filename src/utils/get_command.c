/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 18:03:20 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/08 16:04:31 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_words(const char *str)
{
	int count = 0;
	int in_word = 0;

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
	char *word;

	word = malloc(len + 1);
	if (!word)
		return (NULL);
	strncpy(word, start, len);
	word[len] = '\0';
	return (word);
}

t_token	tokenize_line(char *input)
{
	t_token token;
	int		i = 0, start = 0, word_len = 0, w = 0;

	token.count = count_words(input);
	token.words = malloc(sizeof(char *) * (token.count + 1));
	if (!token.words)
	{
		token.count = 0;
		return (token);
	}
	while (input[i])
	{
		while (is_whitespace(input[i]))
			i++;
		start = i;
		while (input[i] && !is_whitespace(input[i]))
			i++;
		word_len = i - start;
		if (word_len > 0)
		{
			token.words[w++] = extract_word(&input[start], word_len);
		}
	}
	token.words[w] = NULL;
	return (token);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	input[] = "  Hello   world\tthis is\ta test ";
// 	t_token	result = tokenize_line(input);

// 	printf("Nombre de mots : %d\n", result.count);
// 	for (int i = 0; i < result.count; i++)
// 	{
// 		printf("Mot %d : \"%s\"\n", i + 1, result.words[i]);
// 		free(result.words[i]);
// 	}
// 	free(result.words);
// 	return (0);
// }
