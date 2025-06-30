/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:41:28 by hemera            #+#    #+#             */
/*   Updated: 2025/06/30 14:23:39 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_cmd *cmd, t_env *env, int i)
{
	char	**paths;
	char	*path;
	char	*path_temp;

	while (env && strcmp(env->key, "PATH") != 0)
		env = env->next;
	if (!env)
		return (0);
	paths = ft_split(env->value, ':');
	while (paths[++i])
	{
		path_temp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path_temp, cmd->name);
		free(path_temp);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
	}
	i = -1;
	while (paths[++i])
		free(paths[i]);
	free(paths);
	free(cmd);
	return (0);
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
	if (!cmd || !cmd->name)
		return (1);
	if (is_builtin(cmd->name))
		return (exec_builtin(cmd, *env));
	return (exec_external(cmd, *env));
}
