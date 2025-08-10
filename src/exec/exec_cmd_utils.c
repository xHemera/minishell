/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:30:13 by tobesnar          #+#    #+#             */
/*   Updated: 2025/07/29 10:30:13 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_command_not_found(char *cmd_name)
{
	write(2, cmd_name, ft_strlen(cmd_name));
	write(2, ": command not found\n", 20);
	exit(127);
}

void	handle_directory_error(char *cmd_name)
{
	write(2, cmd_name, ft_strlen(cmd_name));
	write(2, ": Is a directory\n", 17);
	exit(126);
}

void	handle_execution_error(char *cmd_name)
{
	perror(cmd_name);
	exit(127);
}

static void	check_file_stat(t_cmd *cmd, char **envp, struct stat *file_stat)
{
	if (S_ISDIR(file_stat->st_mode))
	{
		handle_directory_error(cmd->name);
		exit(126);
	}
	if (access(cmd->name, X_OK) != 0)
	{
		perror(cmd->name);
		free_split(envp);
		exit(126);
	}
	execve(cmd->name, cmd->args, envp);
	if (errno == ENOEXEC)
	{
		perror(cmd->name);
		free_split(envp);
		exit(2);
	}
	handle_execution_error(cmd->name);
	free_split(envp);
	exit(127);
}

void	handle_direct_execution(t_cmd *cmd, char **envp)
{
	struct stat	file_stat;

	if (access(cmd->name, F_OK) != 0)
	{
		handle_execution_error(cmd->name);
		free_split(envp);
		exit(127);
	}
	if (stat(cmd->name, &file_stat) == 0)
		check_file_stat(cmd, envp, &file_stat);
	free_split(envp);
	exit(127);
}
