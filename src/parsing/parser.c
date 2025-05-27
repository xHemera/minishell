/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:25:30 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/22 17:42:33 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->name = NULL;
	cmd->args = NULL;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append = 0;
	cmd->heredoc_delimiter = NULL;
	cmd->is_builtin = false;
	cmd->next = NULL;
	return (cmd);
}

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

static void	free_cmd_fields(t_cmd *tmp)
{
	int	i;

	if (tmp->name)
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
	if (tmp->input_file)
		free(tmp->input_file);
	if (tmp->output_file)
		free(tmp->output_file);
	if (tmp->heredoc_delimiter)
		free(tmp->heredoc_delimiter);
}

void	cmd_list_clear(t_cmd **cmd_list)
{
	t_cmd	*tmp;

	if (!cmd_list || !*cmd_list)
		return ;
	while (*cmd_list)
	{
		tmp = *cmd_list;
		*cmd_list = (*cmd_list)->next;
		free_cmd_fields(tmp);
		free(tmp);
	}
}
