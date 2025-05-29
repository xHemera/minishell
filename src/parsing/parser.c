/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:25:30 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/29 14:06:18 by tobesnar         ###   ########.fr       */
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
