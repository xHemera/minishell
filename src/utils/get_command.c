/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:17:11 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/13 11:20:58 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_builtin_cmd(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(cmd, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(cmd, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "export", 7) == 0)
		return (1);
	if (ft_strncmp(cmd, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	if (ft_strncmp(cmd, "exit", 5) == 0)
		return (1);
	return (0);
}

static int	create_argv(t_cmd *cmd, t_token token)
{
	int	i;

	cmd->argv = malloc(sizeof(char *) * (token.count + 1));
	if (!cmd->argv)
		return (0);
	i = 0;
	while (i < token.count)
	{
		cmd->argv[i] = ft_strdup(token.words[i]);
		if (!cmd->argv[i])
			return (ft_free_split(cmd->argv), 0);
		i++;
	}
	cmd->argv[i] = NULL;
	return (1);
}

static char	**get_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		return (NULL);
	paths = ft_split(envp[i] + 5, ':');
	return (paths);
}

static char	*search_cmd_path(char *cmd, char **paths)
{
	char	*full_path;
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full_path)
			return (NULL);
		if (access(full_path, X_OK) == 0)
		{
			ft_free_split(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

t_cmd	get_command(t_token token, char **envp)
{
	t_cmd	cmd;

	cmd.argv = NULL;
	cmd.path = NULL;
	cmd.is_builtin = 0;
	if (token.count == 0)
		return (cmd);
	if (!create_argv(&cmd, token))
		return (cmd);
	cmd.is_builtin = is_builtin_cmd(cmd.argv[0]);
	if (!cmd.is_builtin)
	{
		char **paths = get_paths(envp);
		cmd.path = search_cmd_path(cmd.argv[0], paths);
	}
	return (cmd);
}
