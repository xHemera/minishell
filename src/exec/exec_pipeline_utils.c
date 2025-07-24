#include "minishell.h"

void	parent_process_cleanup(t_cmd *cmd, int pipe_fd[2], int *in_fd)
{
	if (cmd->next)
	{
		close(pipe_fd[1]);
		if (*in_fd != STDIN_FILENO)
			close(*in_fd);
		*in_fd = pipe_fd[0];
	}
}
