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

int	handle_input_redirect(t_cmd *cmd, char *token, char *next)
{
	char	*clean_next;
	int		result;

	if (!ft_strncmp(token, "<", 2))
	{
		clean_next = remove_quotes(next);
		if (!clean_next)
			return (0);
		result = test_file_access(clean_next, O_RDONLY);
		if (result)
			result = set_input_file(cmd, clean_next);
		free(clean_next);
		return (result);
	}
	else if (!ft_strncmp(token, "<<", 3))
	{
		clean_next = remove_quotes(next);
		if (!clean_next)
			return (0);
		result = set_heredoc(cmd, clean_next);
		free(clean_next);
		return (result);
	}
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
	flags = O_WRONLY | O_CREAT;
	if (!ft_strncmp(token, ">>", 3))
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	result = test_file_access(clean_next, flags);
	if (result)
	{
		if (!ft_strncmp(token, ">", 2))
			result = set_output_file(cmd, clean_next, 0);
		else if (!ft_strncmp(token, ">>", 3))
			result = set_output_file(cmd, clean_next, 1);
	}
	free(clean_next);
	return (result);
}
