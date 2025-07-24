#include "minishell.h"

static void	setup_child_process(t_cmd *cmd)
{
	setup_signals_child();
	redirect_input(cmd);
	redirect_output(cmd);
	if (!cmd->name)
		exit(0);
}

static int	wait_for_child(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

static int	fork_and_execute(t_cmd *cmd, char **envp, t_env *env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		free_split(envp);
		return (1);
	}
	if (pid == 0)
	{
		setup_child_process(cmd);
		execute_command(cmd, envp, env);
	}
	free_split(envp);
	return (wait_for_child(pid));
}

int	exec_external(t_cmd *cmd, t_env *env)
{
	char	**envp;

	if (!cmd->name || cmd->name[0] == '\0')
		return (0);
	envp = env_to_array(env);
	if (!envp)
		return (1);
	return (fork_and_execute(cmd, envp, env));
}
