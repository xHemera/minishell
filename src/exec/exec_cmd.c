/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:41:28 by hemera            #+#    #+#             */
/*   Updated: 2025/06/30 17:01:38 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_cmd *cmd, t_env *env, int i)
{
	char	**paths;
	char	*path;
	char	*path_temp;

	while (env && ft_strncmp(env->key, "PATH", 4) != 0)
		env = env->next;
	if (!env)
		return (NULL);
	paths = ft_split(env->value, ':');
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		path_temp = ft_strjoin(paths[i], "/");
		if (!path_temp)
			continue ;
		path = ft_strjoin(path_temp, cmd->name);
		free(path_temp);
		if (!path)
			continue ;
		if (access(path, F_OK) == 0)
		{
			free_split(paths);
			return (path);
		}
		free(path);
	}
	free_split(paths);
	return (NULL);
}

int	exec_external(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	int		status;
	char	**envp;

	envp = env_to_array(env);
	if (!envp)
		return (1);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		free_split(envp);
		return (1);
	}
	if (pid == 0)
	{
		exec_child(cmd, envp, env);
	}
	waitpid(pid, &status, 0);
	unlink(".heredoc_tmp");
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
	int	exit_code;

	if (!cmd || !cmd->name)
		return (1);
	if (is_builtin(cmd->name))
		exit_code = exec_builtin(cmd, *env);
	else
		exit_code = exec_external(cmd, *env);
	g_signal_received = exit_code;
	return (exit_code);
}
