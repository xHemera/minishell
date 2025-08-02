/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:31:02 by tobesnar          #+#    #+#             */
/*   Updated: 2025/07/29 10:31:02 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	process_pipeline_command(t_cmd *cmd, int pipe_fd[2], int *in_fd,
	t_env **env)
{
	pid_t	pid;

	if (cmd->next && !setup_pipe(pipe_fd))
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		handle_child_process(cmd, pipe_fd, *in_fd, env);
	if (cmd->next)
		cleanup_pipe_resources(pipe_fd, *in_fd);
	*in_fd = pipe_fd[0];
	return (pid);
}

int	exec_pipeline(t_cmd *cmd_list, t_env **env)
{
	int	pipe_fd[2];
	int	in_fd;
	pid_t	last_pid;
	pid_t	pid;
	int	status;

	in_fd = STDIN_FILENO;
	last_pid = 0;
	while (cmd_list)
	{
		pid = process_pipeline_command(cmd_list, pipe_fd, &in_fd, env);
		if (pid == -1)
			return (1);
		last_pid = pid;
		cmd_list = cmd_list->next;
	}
	// Ignore SIGINT pendant l'attente des enfants
	signal(SIGINT, SIG_IGN);
	status = wait_for_children(last_pid);
	signal(SIGINT, handle_sigint);
	return (status);
}
