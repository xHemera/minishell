#include "minishell.h"

static char	*build_path(char *dir, char *cmd_name)
{
	char	*path_temp;
	char	*path;

	path_temp = ft_strjoin(dir, "/");
	if (!path_temp)
		return (NULL);
	path = ft_strjoin(path_temp, cmd_name);
	free(path_temp);
	return (path);
}

char	*get_path(t_cmd *cmd, t_env *env, int i)
{
	char	**paths;
	char	*path;

	while (env && ft_strncmp(env->key, "PATH", 4) != 0)
		env = env->next;
	if (!env)
		return (NULL);
	paths = ft_split(env->value, ':');
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		path = build_path(paths[i], cmd->name);
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

static int	create_child_process(t_cmd *cmd, char **envp, t_env *env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
		exec_child(cmd, envp, env);
	return (pid);
}

int	exec_external(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	int		status;
	char	**envp;

	envp = env_to_array(env);
	if (!envp)
		return (1);
	pid = create_child_process(cmd, envp, env);
	if (pid == -1)
	{
		free_split(envp);
		return (1);
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
	int	original_stdin;
	int	original_stdout;

	if (!cmd || !cmd->name)
		return (1);

	// Save original file descriptors
	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);

	// Handle redirections for simple commands
	if (cmd->input_file || cmd->output_file || cmd->append || cmd->heredoc)
	{
		if (redirect_input(cmd) != 0 || redirect_output(cmd) != 0)
		{
			dup2(original_stdin, STDIN_FILENO);
			dup2(original_stdout, STDOUT_FILENO);
			close(original_stdin);
			close(original_stdout);
			return (1);
		}
	}

	if (is_builtin(cmd->name))
		exit_code = exec_builtin(cmd, *env);
	else
		exit_code = exec_external(cmd, *env);

	// Restore original file descriptors
	dup2(original_stdin, STDIN_FILENO);
	dup2(original_stdout, STDOUT_FILENO);
	close(original_stdin);
	close(original_stdout);

	g_signal_received = exit_code;
	return (exit_code);
}
