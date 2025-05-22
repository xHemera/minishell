/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:12:11 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/22 16:33:08 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	token_list_clear(t_token **lst)
{
	t_token	*tmp;

	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->value);
		free(*lst);
		*lst = tmp;
	}
}

int	handle_quotes(char *line, int *i, char quote_char)
{
	(*i)++;
	while (line[*i] && line[*i] != quote_char)
		(*i)++;
	if (line[*i] == quote_char)
	{
		(*i)++;
		return (1);
	}
	return (0);
}

char	*process_quoted_content(char *raw_token)
{
	char	*result;
	int		i;
	int		j;
	int		len;

	len = ft_strlen(raw_token);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (raw_token[i] == '\'' || raw_token[i] == '\"')
		{
			i++;
			continue ;
		}
		result[j] = raw_token[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}

t_token	*create_new_token(char *token_value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		free(token_value);
		return (NULL);
	}
	new_token->value = token_value;
	new_token->next = NULL;
	return (new_token);
}

t_token	*add_token_to_list(t_token *head, char *token_value)
{
	t_token	*current;
	t_token	*new_token;

	new_token = create_new_token(token_value);
	if (!new_token)
		return (NULL);
	if (!head)
		return (new_token);
	current = head;
	while (current->next)
		current = current->next;
	current->next = new_token;
	return (head);
}
