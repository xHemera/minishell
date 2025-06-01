/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:29:13 by hemera            #+#    #+#             */
/*   Updated: 2025/06/01 14:31:07 by hemera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_process_cleanup(t_cmd *cmd, int pipe_fd[2], int *in_fd)
{
	if (*in_fd != 0)
		close(*in_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*in_fd = pipe_fd[0];
	}
}

void	launch_child_process(t_cmd *cmd, int pipe_fd[2],
		int in_fd, t_env **env)
{
	if (cmd->next)
		dup2(pipe_fd[1], 1);
	if (in_fd != 0)
		dup2(in_fd, 0);
	if (cmd->next)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
	}
	exec_cmd(cmd, env);
	exit(1);
}
