/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:33:22 by tobesnar          #+#    #+#             */
/*   Updated: 2025/07/29 10:33:22 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_regular_input(t_cmd *cmd, char *next)
{
	char	*clean_next;
	int		result;

	clean_next = remove_quotes(next);
	if (!clean_next)
		return (0);
	result = test_file_access(clean_next, O_RDONLY);
	if (!result)
	{
		perror(clean_next);
		free(clean_next);
		return (0);
	}
	if (!set_input_file(cmd, clean_next))
	{
		perror(clean_next);
		free(clean_next);
		return (0);
	}
	free(clean_next);
	return (result);
}

static int	handle_heredoc_input(t_cmd *cmd, char *next)
{
	char	*clean_next;

	clean_next = remove_quotes(next);
	if (!clean_next)
		return (0);
	if (cmd->heredoc)
		free(cmd->heredoc);
	cmd->heredoc = ft_strdup(clean_next);
	free(clean_next);
	if (!cmd->heredoc || handle_heredoc(cmd) != 0)
		return (0);
	return (1);
}

int	handle_input_redirect(t_cmd *cmd, char *token, char *next)
{
	if (!ft_strncmp(token, "<", 2))
		return (handle_regular_input(cmd, next));
	else if (!ft_strncmp(token, "<<", 3))
		return (handle_heredoc_input(cmd, next));
	return (0);
}

int	handle_output_redirect(t_cmd *cmd, char *token, char *next)
{
	char	*clean_next;
	int		result;
	int		flags;

	clean_next = remove_quotes(next);
	if (!clean_next)
		return (0);
	flags = setup_output_flags(token);
	result = test_file_access(clean_next, flags);
	if (!result)
	{
		perror(clean_next);
		free(clean_next);
		return (0);
	}
	result = set_output_redirect(cmd, token, clean_next);
	free(clean_next);
	return (result);
}
