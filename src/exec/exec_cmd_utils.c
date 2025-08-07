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

static void	handle_command_not_found(char *cmd_name)
{
	write(2, cmd_name, ft_strlen(cmd_name));
	write(2, ": command not found\n", 20);
	exit(127);
}

static void	handle_directory_error(char *cmd_name)
{
	write(2, cmd_name, ft_strlen(cmd_name));
	write(2, ": Is a directory\n", 17);
	exit(126);
}

static void	handle_execution_error(char *cmd_name)
{
	perror(cmd_name);
	exit(127);
}

void	handle_direct_execution(t_cmd *cmd, char **envp)
{
	struct stat	file_stat;

	if (access(cmd->name, F_OK) != 0)
	{
		handle_execution_error(cmd->name); // message : No such file or directory
		exit(127);
	}
	if (stat(cmd->name, &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
		{
			handle_directory_error(cmd->name);
			exit(126);
		}
		if (access(cmd->name, X_OK) != 0)
		{
			handle_directory_error(cmd->name);
			exit(126);
		}
		if (execve(cmd->name, cmd->args, envp) == -1)
		{
			handle_execution_error(cmd->name);
			exit(126);
		}
	}
	exit(127);
}


void	execute_command(t_cmd *cmd, char **envp, t_env *env)
{
	char	*path;

	if (!cmd->name || cmd->name[0] == '\0')
		exit(0);
	if (ft_strchr(cmd->name, '/') || cmd->name[0] == '.')
		handle_direct_execution(cmd, envp);
	else
	{
		path = get_path(cmd, env);
		if (path)
		{
			if (execve(path, cmd->args, envp) == -1)
			{
				handle_execution_error(cmd->name);
				exit(126);
			}
		}
		else
		{
			handle_command_not_found(cmd->name);
			exit(127);
		}
	}
	exit(0);
}
