#include "minishell.h"



static int	handle_heredoc_input(t_cmd *cmd)
{
	int	fd;

	if (!create_heredoc_file(cmd))
	{
		perror("heredoc");
		exit(1);
	}
	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd != -1)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		unlink(".heredoc_tmp");
	}
	else
	{
		perror("heredoc");
		exit(1);
	}
	return (0);
}

int	handle_file_input(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->input_file, O_RDONLY);
	if (fd != -1)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
	{
		perror(cmd->input_file);
		return (-1);  // Just return error, don't change stdin
	}
	return (0);
}

int	redirect_input(t_cmd *cmd)
{
	if (cmd->heredoc)
		return (handle_heredoc_input(cmd));
	else if (cmd->input_file)
	{
		if (handle_file_input(cmd) != 0)
			return (0);  // Continue even if input redirection fails
	}
	return (0);
}

static int	open_output_file(t_cmd *cmd)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (cmd->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	fd = open(cmd->output_file, flags, 0644);
	if (fd == -1)
	{
		perror(cmd->output_file);
		return (-1);
	}
	return (fd);
}

int	redirect_output(t_cmd *cmd)
{
	int	fd;

	if (cmd->output_file)
	{
		fd = open_output_file(cmd);
		if (fd != -1)
		{
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		// If redirection fails, just continue without redirecting
		// This allows the command to write to the pipe normally
	}
	return (0);  // Always return success to continue pipeline
}
