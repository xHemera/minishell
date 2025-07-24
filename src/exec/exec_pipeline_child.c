#include "minishell.h"

static void	handle_path_execution(t_cmd *cmd, char **envp, t_env *env)
{
	char	*path;

	path = get_path(cmd, env);
	if (path)
	{
		if (execve(path, cmd->args, envp) == -1)
			perror(cmd->name);
	}
	else
	{
		write(2, cmd->name, ft_strlen(cmd->name));
		write(2, ": command not found\n", 20);
	}
}

static void	handle_child_external(t_cmd *cmd, char **envp, t_env *env)
{
	if (ft_strchr(cmd->name, '/') || cmd->name[0] == '.')
		handle_direct_execution(cmd, envp);
	else
		handle_path_execution(cmd, envp, env);
	exit(127);
}

void	launch_child_process(t_cmd *cmd, int pipe_fd[2], int in_fd, t_env **env)
{
	char	**envp;

	setup_signals_child();
	envp = env_to_array(*env);
	if (!envp)
		exit(1);
	setup_child_redirections(cmd, pipe_fd, in_fd);
	if (!cmd->name || cmd->name[0] == '\0')
	{
		free_split(envp);
		exit(0);
	}
	if (cmd->is_builtin)
		handle_child_builtin(cmd, envp, *env);
	else
		handle_child_external(cmd, envp, *env);
}
