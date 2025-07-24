/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_process.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:44:01 by marvin            #+#    #+#             */
/*   Updated: 2025/07/24 21:44:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (0);
	}
	return (1);
}

void	handle_child_process(t_cmd *cmd, int pipe_fd[2], int in_fd,
	t_env **env)
{
	char	**envp;

	envp = env_to_array(*env);
	if (!envp)
		exit(1);
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (cmd->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	if (cmd->is_builtin)
	{
		free_split(envp);
		exit(exec_builtin(cmd, *env));
	}
	exec_child(cmd, envp, *env);
}

void	cleanup_pipe_resources(int pipe_fd[2], int in_fd)
{
	close(pipe_fd[1]);
	if (in_fd != STDIN_FILENO)
		close(in_fd);
}

int	wait_for_children(int last_pid)
{
	int	status;
	int	pid;
	int	last_status;

	last_status = 0;
	pid = wait(&status);
	while (pid > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
		pid = wait(&status);
	}
	return (last_status);
}
