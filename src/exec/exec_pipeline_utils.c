#include "minishell.h"

static void	setup_pipeline_redirects(t_cmd *cmd, int pipe_fd[2], int in_fd)
{
	if (cmd->next)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], STDOUT_FILENO);
		close(pipe_fd[1]);
	}
	if (in_fd != 0)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
}

void	launch_child_process(t_cmd *cmd, int pipe_fd[2], int in_fd, t_env **env)
{
	char	**envp;

	if (is_builtin(cmd->name))
	{
		setup_pipeline_redirects(cmd, pipe_fd, in_fd);
		if (cmd->input_file || cmd->output_file || cmd->append || cmd->heredoc)
		{
			// In a pipeline, continue execution even if redirections fail
			redirect_input(cmd);
			redirect_output(cmd);
		}
		exit(exec_builtin(cmd, *env));
	}
	else
	{
		setup_pipeline_redirects(cmd, pipe_fd, in_fd);
		if (cmd->input_file || cmd->output_file || cmd->append || cmd->heredoc)
		{
			// In a pipeline, continue execution even if redirections fail
			redirect_input(cmd);
			redirect_output(cmd);
		}
		envp = env_to_array(*env);
		if (!envp)
			exit(1);
		exec_child(cmd, envp, *env);
	}
}

void	parent_process_cleanup(t_cmd *cmd, int pipe_fd[2], int *in_fd)
{
	if (*in_fd != 0)
		close(*in_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*in_fd = pipe_fd[0];
	}
	else
		*in_fd = 0;
}
