/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:41:28 by hemera            #+#    #+#             */
/*   Updated: 2025/06/01 13:42:51 by hemera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_external(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	int		status;
	char	**envp;

	envp = env_to_array(env);

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		execve(cmd->name, cmd->args, envp);
		perror("execve");
		exit(127);
	}
	waitpid(pid, &status, 0);
	free_split(envp);
	return (WEXITSTATUS(status));
}

int	is_state_changing_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	return (is_str_builtin(cmd_name, "cd", 2)
		|| is_str_builtin(cmd_name, "export", 6)
		|| is_str_builtin(cmd_name, "unset", 5)
		|| is_str_builtin(cmd_name, "exit", 4));
}

int	exec_cmd(t_cmd *cmd, t_env **env)
{
	if (!cmd || !cmd->name)
		return (1);
	if (is_builtin(cmd->name))
		return (exec_builtin(cmd, *env));
	return (exec_external(cmd, *env));
}
