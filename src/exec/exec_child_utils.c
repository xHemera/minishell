/* ***********int	handle_heredoc_input(t_cmd *cmd)************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:47:22 by tlize             #+#    #+#             */
/*   Updated: 2025/06/30 14:31:07 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_heredoc_input(t_cmd *cmd)
{
	int	fd;

	if (!create_heredoc_file(cmd))
	{
		perror("heredoc");
		exit(1);
	}
	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd != -1)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		unlink(".heredoc_tmp");
	}
	else
	{
		perror("heredoc");
		exit(1);
	}
	return (0);
}

int	handle_file_input(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->input_file, O_RDONLY);
	if (fd != -1)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
	{
		perror(cmd->input_file);
		exit(1);
	}
	return (0);
}

int	redirect_input(t_cmd *cmd)
{
	if (cmd->heredoc)
		return (handle_heredoc_input(cmd));
	else if (cmd->input_file)
		return (handle_file_input(cmd));
	return (0);
}

int	redirect_output(t_cmd *cmd)
{
	int	fd;
	int	flags;

	fd = -1;
	flags = O_WRONLY | O_CREAT;
	if (cmd->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	if (cmd->output_file)
	{
		fd = open(cmd->output_file, flags, 0644);
		if (fd != -1)
		{
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else
		{
			perror(cmd->output_file);
			exit(1);
		}
	}
	return (0);
}
