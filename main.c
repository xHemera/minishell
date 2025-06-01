/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:53:18 by tobesnar          #+#    #+#             */
/*   Updated: 2025/06/01 13:12:58 by hemera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_str_builtin(const char *cmd, const char *name, size_t len)
{
	return (ft_strncmp(cmd, name, len) == 0
		&& (cmd[len] == '\0' || cmd[len] == ' '));
}

static int	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (is_str_builtin(cmd_name, "echo", 4))
		return (1);
	if (is_str_builtin(cmd_name, "cd", 2))
		return (1);
	if (is_str_builtin(cmd_name, "pwd", 3))
		return (1);
	if (is_str_builtin(cmd_name, "export", 6))
		return (1);
	if (is_str_builtin(cmd_name, "unset", 5))
		return (1);
	if (is_str_builtin(cmd_name, "env", 3))
		return (1);
	if (is_str_builtin(cmd_name, "exit", 4))
		return (1);
	return (0);
}

static int	exec_cmd(t_cmd *cmd, t_env **env)
{
	if (!cmd || !cmd->name)
		return (1);
	if (is_builtin(cmd->name))
		return (exec_builtin(cmd, *env));
	return (exec_external(cmd, *env));
}

static int	exec_pipeline(t_cmd *cmd_list, t_env **env)
{
	int		pipe_fd[2];
	int		pid;
	int		in_fd;
	t_cmd	*cmd;

	in_fd = 0;
	cmd = cmd_list;
	while (cmd)
	{
		if (cmd->next && pipe(pipe_fd) == -1)
			return (perror("pipe"), 1);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), 1);
		else if (pid == 0)
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
		else
		{
			if (in_fd != 0)
				close(in_fd);
			if (cmd->next)
			{
				close(pipe_fd[1]);
				in_fd = pipe_fd[0];
			}
		}
		cmd = cmd->next;
	}
	while (wait(NULL) > 0)
		;
	return (0);
}

static void	parse_and_exec(char *line, t_env **env)
{
	char	**segments;
	t_cmd	*cmd_list;
	t_cmd	*last_cmd;
	t_cmd	*cmd;
	int		i;

	segments = split_pipe_aware(line);
	if (!segments)
		return ;
	cmd_list = NULL;
	last_cmd = NULL;
	i = 0;
	while (segments[i])
	{
		cmd = parse_segment(segments[i]);
		if (!cmd)
		{
			free_cmd_list(cmd_list);
			cmd_list = NULL;
			break ;
		}
		if (!cmd_list)
			cmd_list = cmd;
		else
			last_cmd->next = cmd;
		last_cmd = cmd;
		i++;
	}
	if (cmd_list)
	{
		if (!cmd_list->next)
			exec_cmd(cmd_list, env);
		else
			exec_pipeline(cmd_list, env);
	}
	free_cmd_list(cmd_list);
	free_split(segments);
}

static void	minishell_loop(t_env **env)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			exit(0);
		if (*line)
		{
			add_history(line);
			parse_and_exec(line, env);
		}
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	data;

	(void)argc;
	(void)argv;
	data.env = env_init(envp);
	minishell_loop(&data.env);
	free_env(&data.env);
	return (0);
}
