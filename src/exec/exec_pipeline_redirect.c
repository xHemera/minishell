#include "minishell.h"

void	setup_child_redirections(t_cmd *cmd, int pipe_fd[2], int in_fd)
{
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (cmd->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
}

void	handle_child_builtin(t_cmd *cmd, char **envp, t_env *env)
{
	free_split(envp);
	exit(exec_builtin(cmd, env));
}
