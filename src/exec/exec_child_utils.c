/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:42:35 by marvin            #+#    #+#             */
/*   Updated: 2025/07/24 21:42:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_heredoc_input(void)
{
	int	fd;

	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd == -1)
	{
		perror("heredoc");
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink(".heredoc_tmp");
	return (0);
}

static int	handle_file_input(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->input_file, O_RDONLY);
	if (fd == -1)
	{
		perror(cmd->input_file);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	redirect_input(t_cmd *cmd)
{
	if (cmd->heredoc)
		return (handle_heredoc_input());
	else if (cmd->input_file)
		return (handle_file_input(cmd));
	return (0);
}

static int	open_output_file_with_flags(t_cmd *cmd)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (cmd->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(cmd->output_file, flags, 0644);
	if (fd == -1)
	{
		perror(cmd->output_file);
		return (-1);
	}
	return (fd);
}

int	redirect_output(t_cmd *cmd)
{
	int	fd;

	if (!cmd->output_file)
		return (0);
	fd = open_output_file_with_flags(cmd);
	if (fd == -1)
		return (1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}
