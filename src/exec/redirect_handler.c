#include "minishell.h"

int	create_heredoc_file(t_cmd *cmd)
{
	char	*line;
	int		fd;

	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror(".heredoc_tmp"), 0);
	setup_signals_heredoc();
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
		{
			if (g_signal_received == SIGINT)
			{
				close(fd);
				unlink(".heredoc_tmp");
				exit(130);
			}
			break ;
		}
		if (!ft_strncmp(line, cmd->heredoc, ft_strlen(cmd->heredoc))
			&& line[ft_strlen(cmd->heredoc)] == '\n')
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		free(line);
	}
	close(fd);
	setup_signals_child();
	return (1);
}

static int	handle_heredoc_redirect(t_cmd *cmd)
{
	int	fd;

	if (!create_heredoc_file(cmd))
		return (1);
	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd == -1)
	{
		perror("heredoc");
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink(".heredoc_tmp");
	return (0);
}

static int	handle_file_redirect(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->input_file, O_RDONLY);
	if (fd == -1)
	{
		perror(cmd->input_file);
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	setup_input_redirect(t_cmd *cmd)
{
	if (cmd->heredoc)
		return (handle_heredoc_redirect(cmd));
	else if (cmd->input_file)
		return (handle_file_redirect(cmd));
	return (0);
}

static int	open_output_file_with_flags(t_cmd *cmd)
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

int	setup_output_redirect(t_cmd *cmd)
{
	int	fd;

	if (!cmd->output_file)
		return (0);
	fd = open_output_file_with_flags(cmd);
	if (fd == -1)
		return (1);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	setup_redirections(t_cmd *cmd)
{
	if (setup_input_redirect(cmd))
		return (1);
	if (setup_output_redirect(cmd))
		return (1);
	return (0);
}
