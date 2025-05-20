/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:25:30 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/13 17:37:30 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*parse_line(char *line)
{
	t_token	*tokens;
	t_cmd	*cmd;

	tokens = tokenize_input(line);
	if (!tokens)
		return (NULL);
	cmd = parse_cmd(tokens);

	return (cmd);
}

void	cmd_list_clear(t_cmd **cmd_list)
{
	t_cmd	*tmp;
	int		i;

	while (*cmd_list)
	{
		tmp = *cmd_list;
		*cmd_list = (*cmd_list)->next;
		free(tmp->name);
		if (tmp->args)
		{
			i = 0;
			while (tmp->args[i])
			{
				free(tmp->args[i]);
				i++;
			}
			free(tmp->args);
		}
		free(tmp);
	}
}
