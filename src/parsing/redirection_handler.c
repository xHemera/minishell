/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:26:14 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/29 17:47:46 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_input_heredoc(t_cmd *cmd, char *token, char *next)
{
	if (!ft_strncmp(token, "<", 2))
	{
		free(cmd->input_file);
		cmd->input_file = ft_strdup(next);
		if (!cmd->input_file)
			return (0);
		return (1);
	}
	if (!ft_strncmp(token, "<<", 3))
	{
		free(cmd->heredoc);
		cmd->heredoc = ft_strdup(next);
		if (!cmd->heredoc)
			return (0);
		return (1);
	}
	return (0);
}

static int	handle_output(t_cmd *cmd, char *token, char *next)
{
	if (!ft_strncmp(token, ">", 2))
	{
		free(cmd->output_file);
		cmd->output_file = ft_strdup(next);
		if (!cmd->output_file)
			return (0);
		cmd->append = 0;
		return (1);
	}
	if (!ft_strncmp(token, ">>", 3))
	{
		free(cmd->output_file);
		cmd->output_file = ft_strdup(next);
		if (!cmd->output_file)
			return (0);
		cmd->append = 1;
		return (1);
	}
	return (0);
}

int	handle_redirect(t_cmd *cmd, char **tokens, int *i)
{
	if (!tokens[*i + 1])
		return (0);
	if (handle_input_heredoc(cmd, tokens[*i], tokens[*i + 1]))
	{
		*i += 2;
		return (1);
	}
	if (handle_output(cmd, tokens[*i], tokens[*i + 1]))
	{
		*i += 2;
		return (1);
	}
	return (0);
}

