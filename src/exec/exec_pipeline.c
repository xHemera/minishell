/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:41:08 by hemera            #+#    #+#             */
/*   Updated: 2025/06/01 13:41:08 by hemera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parent_process_cleanup(t_cmd *cmd, int pipe_fd[2], int *in_fd)
{
	if (*in_fd != 0)
		close(*in_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*in_fd = pipe_fd[0];
	}
}

static void	launch_child_process(t_cmd *cmd, int pipe_fd[2], int in_fd, t_env **env)
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

int	exec_pipeline(t_cmd *cmd_list, t_env **env)
{
	t_cmd	*cmd = cmd_list;
	int		in_fd = 0;
	int		pipe_fd[2];
	int		pid;

	while (cmd)
	{
		if (cmd->next && is_state_changing_builtin(cmd->name))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->name, 2);
			ft_putstr_fd(": BRR BRR PATAPIM\n", 2);
			ft_putstr_fd("Dans ce cas il faut exec dans le processus parent (on modif l'état du shell)\n", 2);
			cmd = cmd->next;
			continue ;
		}
		if (cmd->next && pipe(pipe_fd) == -1)
			return (perror("pipe"), 1);
		if (!cmd->next && is_state_changing_builtin(cmd->name))
			return (handle_builtin_in_pipeline(cmd, in_fd, env));
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		if (pid == 0)
			launch_child_process(cmd, pipe_fd, in_fd, env);
		parent_process_cleanup(cmd, pipe_fd, &in_fd);
		cmd = cmd->next;
	}
	while (wait(NULL) > 0)
		;
	return (0);
}
