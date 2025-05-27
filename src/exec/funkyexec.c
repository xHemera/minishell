/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funkyexec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:25:00 by tlize             #+#    #+#             */
/*   Updated: 2025/05/27 18:50:02 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*find_path_env(t_env *envp)
{
	while (envp)
	{
		if (ft_strncmp(envp->key, "PATH", 5) == 0)
			return (envp->value);
		envp = envp->next;
	}
	return (NULL);
}

static char	**env_to_array(t_env *env)
{
	int		count;
	int		i;
	t_env	*tmp;
	char	**array;
	char	*temp_str;

	count = 0;
	tmp = env;
	while (tmp && ++count)
		tmp = tmp->next;
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	tmp = env;
	i = 0;
	while (tmp && i < count)
	{
		temp_str = ft_strjoin(tmp->key, "=");
		if (!temp_str)
			return (free_env_array(array, i), NULL);
		array[i] = ft_strjoin(temp_str, tmp->value ? tmp->value : "");
		free(temp_str);
		if (!array[i])
			return (free_env_array(array, i), NULL);
		tmp = tmp->next;
		i++;
	}
	array[i] = NULL;
	return (array);
}

static void	free_env_array(char **env_array, int count)
{
	int	i;

	if (!env_array)
		return ;
	i = 0;
	while (i < count && env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}

static char	*find_command_path(char *cmd_name, char *path_env)
{
	char	**paths;
	char	*full_path;
	char	*temp_path;
	int		i;

	if (!cmd_name || !path_env)
		return (NULL);
	if (access(cmd_name, F_OK) == 0)
		return (ft_strdup(cmd_name));
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		temp_path = ft_strjoin(paths[i], "/");
		if (!temp_path)
			return (ft_free_split(paths), NULL);
		full_path = ft_strjoin(temp_path, cmd_name);
		free(temp_path);
		if (full_path && access(full_path, X_OK) == 0)
			return (ft_free_split(paths), full_path);
		free(full_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

int	exec_commande(t_cmd *cmd, t_env *envp)
{
	pid_t	pid;
	int		status;
	char	*path_env;
	char	**env_array;
	char	*cmd_path;

	if (!cmd || !cmd->name)
		return (1);
	path_env = find_path_env(envp);
	if (!path_env)
		return (ft_putstr_fd("PATH not found\n", 2), 127);
	env_array = env_to_array(envp);
	if (!env_array)
		return (1);
	cmd_path = find_command_path(cmd->name, path_env);
	if (!cmd_path)
		return (free_env_array(env_array, -1),
			ft_putstr_fd("command not found\n", 2), 127);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), free_env_array(env_array, -1),
			free(cmd_path), 1);
	if (pid == 0)
	{
		if (execve(cmd_path, cmd->args, env_array) == -1)
		{
			perror("execve");
			free_env_array(env_array, -1);
			free(cmd_path);
			exit(127);
		}
	}
	free_env_array(env_array, -1);
	free(cmd_path);
	if (waitpid(pid, &status, 0) == -1)
		return (perror("waitpid"), 1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}
