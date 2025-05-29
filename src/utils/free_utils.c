/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 13:58:03 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/29 14:44:15 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->name)
		free(cmd->name);
	if (cmd->args)
	{
		for (i = 0; cmd->args[i]; i++)
			free(cmd->args[i]);
		free(cmd->args);
	}
	if (cmd->input_file)
		free(cmd->input_file);
	if (cmd->output_file)
		free(cmd->output_file);
	if (cmd->heredoc_delimiter)
		free(cmd->heredoc_delimiter);
	free(cmd);
}


void	cmd_list_clear(t_cmd **cmd_list)
{
	t_cmd	*tmp;

	while (cmd_list && *cmd_list)
	{
		tmp = (*cmd_list)->next;
		free_cmd(*cmd_list);
		*cmd_list = tmp;
	}
}

void	free_args(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}
