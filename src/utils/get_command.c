/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 10:53:09 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/13 10:55:49 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_builtin_cmd(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset") || !ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

static char	*join_and_check(char *path, char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full)
		return (NULL);
	if (access(full, X_OK) == 0)
		return (full);
	free(full);
	return (NULL);
}

static char	*find_cmd_path(char *cmd, char **env)
{
	char	*path_env;
	char	**paths;
	char	*full;
	int		i;

	if (!cmd || ft_strchr(cmd, '/'))
		return (access(cmd, X_OK) == 0 ? ft_strdup(cmd) : NULL);
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	full = NULL;
	while (paths[i] && !full)
	{
		full = join_and_check(paths[i], cmd);
		i++;
	}
	ft_free_split(paths);
	return (full);
}

static char	*find_cmd_path(char *cmd, char **env)
{
	char	*path_env;
	char	**paths;
	char	*full;
	int		i;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_env = getenv("PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	full = NULL;
	while (paths[i] && !full)
	{
		full = join_and_check(paths[i], cmd);
		i++;
	}
	ft_free_split(paths);
	return (full);
}

t_cmd	get_command(t_token token, char **env)
{
	t_cmd	cmd;
	int		ok;

	cmd.argv = NULL;
	cmd.path = NULL;
	cmd.is_builtin = 0;
	if (token.count == 0 || !token.words)
		return (cmd);
	ok = fill_argv(&cmd, token);
	if (!ok)
		return (cmd);
	cmd.is_builtin = is_builtin_cmd(cmd.argv[0]);
	if (cmd.is_builtin)
		cmd.path = ft_strdup(cmd.argv[0]);
	else
		cmd.path = find_cmd_path(cmd.argv[0], env);
	return (cmd);
}
