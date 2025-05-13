/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:12:15 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/13 16:17:20 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*extract_token(char *line, int *i)
{
	int		start;
	char	quote;
	char	*token;

	while (is_whitespace(line[*i]))
		(*i)++;
	start = *i;
	quote = 0;
	while (line[*i])
	{
		if (!quote && (line[*i] == '\'' || line[*i] == '\"'))
			quote = line[(*i)++];
		else if (quote && line[*i] == quote)
		{
			(*i)++;
			quote = 0;
		}
		else if (!quote && is_whitespace(line[*i]))
			break ;
		else
			(*i)++;
	}
	token = ft_substr(line, start, *i - start);
	return (token);
}

static t_token	*add_token_to_list(t_token *head, char *token)
{
	t_token	*curr;
	t_token	*tmp;

	curr = malloc(sizeof(t_token));
	if (!curr)
		return (NULL);
	curr->value = token;
	curr->next = NULL;
	if (!head)
		return (curr);
	else
	{
		tmp = head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = curr;
	}
	return (head);
}

t_token	*tokenize_input(char *input)
{
	t_token	*head;
	char	*token;
	int		i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		token = extract_token(input, &i);
		if (!token)
			break ;
		token = ft_strtrim(token, "\"\'");
		head = add_token_to_list(head, token);
	}
	return (head);
}
