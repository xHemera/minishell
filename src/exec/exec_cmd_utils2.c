/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 10:29:39 by tobesnar          #+#    #+#             */
/*   Updated: 2025/08/10 20:33:15 by hemera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_path_execution(char *path, t_cmd *cmd, char **envp)
{
	execve(path, cmd->args, envp);
	if (errno == ENOEXEC)
	{
		perror(cmd->name);
		free(path);
		free_split(envp);
		exit(2);
	}
	handle_execution_error(cmd->name);
	free(path);
	free_split(envp);
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
			handle_path_execution(path, cmd, envp);
		else
		{
			handle_command_not_found(cmd->name);
			exit(127);
		}
	}
	free_split(envp);
	exit(127);
}
