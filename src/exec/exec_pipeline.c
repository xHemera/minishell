/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:41:08 by hemera            #+#    #+#             */
/*   Updated: 2025/06/01 14:33:24 by hemera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_builtin_in_pipeline(t_cmd *cmd, int in_fd, t_env **env)
{
	int	saved_stdin;
	int	result;

	saved_stdin = -1;
	if (in_fd != 0)
	{
		saved_stdin = dup(0);
		dup2(in_fd, 0);
		close(in_fd);
	}
	result = exec_builtin(cmd, *env);
	if (saved_stdin != -1)
	{
		dup2(saved_stdin, 0);
		close(saved_stdin);
	}
	return (result);
}

static int	handle_state_changing_builtin(t_cmd **cmd, int pipe_fd[2])
{
	if ((*cmd)->next && pipe(pipe_fd) == -1)
		return (perror("pipe"), 1);
	return (0);
}

static int	fork_and_launch(t_cmd *cmd, int pipe_fd[2], int in_fd, t_env **env)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	if (pid == 0)
		launch_child_process(cmd, pipe_fd, in_fd, env);
	return (pid);
}

static int	exec_pipeline_loop(t_cmd *cmd_list, t_env **env, int *last_pid)
{
	t_cmd	*cmd;
	int		in_fd;
	int		pipe_fd[2];
	int		ret;
	int		pid;

	cmd = cmd_list;
	in_fd = 0;
	*last_pid = -1;
	while (cmd)
	{
		ret = handle_state_changing_builtin(&cmd, pipe_fd);
		if (ret == 1)
			continue ;
		else if (ret == 2)
			return (1);
		if (!cmd->next && is_state_changing_builtin(cmd->name))
			return (handle_builtin_in_pipeline(cmd, in_fd, env));
		pid = fork_and_launch(cmd, pipe_fd, in_fd, env);
		if (pid == -1)
			return (1);
		if (!cmd->next)
			*last_pid = pid;
		parent_process_cleanup(cmd, pipe_fd, &in_fd);
		cmd = cmd->next;
	}
	return (in_fd);
}

int	exec_pipeline(t_cmd *cmd_list, t_env **env)
{
	int	in_fd;
	int	status;
	int	last_exit_code;
	int	last_pid;
	int	waited_pid;

	last_exit_code = 0;
	in_fd = exec_pipeline_loop(cmd_list, env, &last_pid);
	if (in_fd < 0)
		return (1);
	while ((waited_pid = wait(&status)) > 0)
	{
		if (waited_pid == last_pid)
			last_exit_code = WEXITSTATUS(status);
	}
	if (in_fd != 0)
		close(in_fd);
	return (last_exit_code);
}
