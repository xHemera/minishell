/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_file_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:32:48 by tobesnar          #+#    #+#             */
/*   Updated: 2025/07/29 10:32:48 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_input_file(t_cmd *cmd, char *file)
{
	if (cmd->input_file)
		free(cmd->input_file);
	cmd->input_file = ft_strdup(file);
	return (cmd->input_file != NULL);
}

int	set_output_file(t_cmd *cmd, char *file, int append)
{
	if (cmd->output_file)
		free(cmd->output_file);
	cmd->output_file = ft_strdup(file);
	cmd->append = append;
	return (cmd->output_file != NULL);
}

static int	check_dir_access(char *file)
{
	char	*dir;
	char	*last_slash;
	int		result;

	dir = ft_strdup(file);
	if (!dir)
		return (0);
	last_slash = ft_strrchr(dir, '/');
	if (last_slash)
	{
		*last_slash = '\0';
		result = (access(dir, W_OK) == 0);
	}
	else
		result = (access(".", W_OK) == 0);
	free(dir);
	return (result);
}

int	test_file_access(char *file, int flags)
{
	if (access(file, F_OK) == 0)
	{
		if (flags & O_WRONLY)
			return (access(file, W_OK) == 0);
		return (access(file, R_OK) == 0);
	}
	else
	{
		if (flags & O_CREAT)
			return (check_dir_access(file));
		return (0);
	}
}
