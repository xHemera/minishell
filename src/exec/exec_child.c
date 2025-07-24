/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:42:37 by marvin            #+#    #+#             */
/*   Updated: 2025/07/24 21:42:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_file_permissions(t_cmd *cmd, char **envp,
	struct stat *file_stat)
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

	path = get_path(cmd, env);
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
