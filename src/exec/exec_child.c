/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:47:22 by tlize             #+#    #+#             */
/*   Updated: 2025/06/30 14:31:07 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_heredoc_file(t_cmd *cmd)
{
	char	*line;
	int		fd;

	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror(".heredoc_tmp"), 0);
	setup_signals_heredoc();
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
		{
			if (g_signal_received == 130)
			{
				close(fd);
				unlink(".heredoc_tmp");
				exit(130);
			}
			break ;
		}
		if (!ft_strncmp(line, cmd->heredoc, ft_strlen(cmd->heredoc))
			&& line[ft_strlen(cmd->heredoc)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	setup_signals_child();
	return (1);
}

static void	check_file_permissions(t_cmd *cmd, char **envp, struct stat *file_stat)
{
	if (S_ISDIR(file_stat->st_mode))
	{
		write(2, cmd->name, ft_strlen(cmd->name));
		write(2, ": Is a directory\n", 17);
		free_split(envp);
		exit(126);
	}
	if (access(cmd->name, X_OK) != 0)
	{
		perror(cmd->name);
		free_split(envp);
		exit(126);
	}
}

static void	execute_file(t_cmd *cmd, char **envp)
{
	execve(cmd->name, cmd->args, envp);
	if (errno == ENOEXEC)
	{
		free_split(envp);
		exit(0);
	}
	perror("execve");
	free_split(envp);
	exit(127);
}

static void	handle_absolute_path(t_cmd *cmd, char **envp)
{
	struct stat	file_stat;

	if (access(cmd->name, F_OK) == 0)
	{
		if (stat(cmd->name, &file_stat) == 0)
			check_file_permissions(cmd, envp, &file_stat);
		execute_file(cmd, envp);
	}
	else
	{
		perror(cmd->name);
		free_split(envp);
		exit(127);
	}
}

static void	handle_relative_path(t_cmd *cmd, char **envp, t_env *env)
{
	char	*path;

	path = get_path(cmd, env, -1);
	if (path)
		execve(path, cmd->args, envp);
	else
	{
		write(2, cmd->name, ft_strlen(cmd->name));
		write(2, ": command not found\n", 20);
		free_split(envp);
		exit(127);
	}
	perror("execve");
	free_split(envp);
	exit(127);
}

int	exec_child(t_cmd *cmd, char **envp, t_env *env)
{
	setup_signals_child();
	redirect_input(cmd);
	redirect_output(cmd);
	if (!cmd->name || cmd->name[0] == '\0')
	{
		free_split(envp);
		exit(0);
	}
	if (ft_strchr(cmd->name, '/') || cmd->name[0] == '.')
		handle_absolute_path(cmd, envp);
	else
		handle_relative_path(cmd, envp, env);
	return (0);
}
