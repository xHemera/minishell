#include "minishell.h"

static char	*join_path_and_cmd(char *path, char *cmd)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(path, "/");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, cmd);
	free(temp);
	return (result);
}

static char	*find_executable_in_path(char *cmd, char **paths)
{
	int		i;
	char	*full_path;

	i = 0;
	while (paths[i])
	{
		full_path = join_path_and_cmd(paths[i], cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*get_path(t_cmd *cmd, t_env *env)
{
	char	*path_value;
	char	**paths;
	char	*result;

	path_value = NULL;
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 5) == 0)
		{
			path_value = env->value;
			break ;
		}
		env = env->next;
	}
	if (!path_value)
		return (NULL);
	paths = ft_split(path_value, ':');
	if (!paths)
		return (NULL);
	result = find_executable_in_path(cmd->name, paths);
	free_split(paths);
	return (result);
}
