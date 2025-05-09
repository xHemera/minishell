/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   tokenize.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tobesnar <tobesnar@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/05/08 16:47:43 by tobesnar		  #+#	#+#			 */
/*   Updated: 2025/05/08 16:52:20 by tobesnar		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_words(const char *str)
{
	int 	count = 0;
	int		in_word = 0;
	int		in_quotes = 0;
	char	quote_char = '\0';

	while (*str)
	{
		if (is_whitespace(*str) && !in_quotes)
			in_word = 0;
		else if (*str == '\'' || *str == '"')
		{
			if (!in_quotes)
			{
				in_quotes = 1;
				quote_char = *str;
			}
			else if (*str == quote_char)
				in_quotes = 0;
		}
		else if (!in_word)
		{
			in_word = 1;
			count++;
		}
		str++;
	}
	return (count);
}

t_token	tokenize_line(char *input)
{
	t_token	token;
	int		i;
	int		start;
	int		word_len;
	int		w;

	i = 0;
	w = 0;
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
		if (input[i] == '\'' || input[i] == '"')
			process_quoted_word(input, &i, &start, &word_len);
		else
			process_normal_word(input, &i, &start, &word_len);
		if (word_len > 0)
			token.words[w++] = extract_word(&input[start], word_len);
	}
	token.words[w] = NULL;
	return (token);
}
