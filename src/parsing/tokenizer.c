/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:12:15 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/22 16:35:55 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	find_token_end(char *line, int start)
{
	int	i;

	i = start;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			if (!handle_quotes(line, &i, line[i]))
				break ;
		}
		else if (is_whitespace(line[i]))
			break ;
		else
			i++;
	}
	return (i);
}

static char	*extract_token(char *line, int *i)
{
	int		start;
	int		end;
	char	*raw_token;
	char	*processed_token;

	while (is_whitespace(line[*i]))
		(*i)++;
	start = *i;
	end = find_token_end(line, start);
	*i = end;
	if (end == start)
		return (NULL);
	raw_token = ft_substr(line, start, end - start);
	if (!raw_token)
		return (NULL);
	processed_token = process_quoted_content(raw_token);
	free(raw_token);
	return (processed_token);
}

t_token	*tokenize_input(char *input)
{
	t_token	*head;
	char	*token_value;
	int		i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		token_value = extract_token(input, &i);
		if (!token_value)
			continue ;
		head = add_token_to_list(head, token_value);
		if (!head)
		{
			token_list_clear(&head);
			return (NULL);
		}
	}
	return (head);
}
