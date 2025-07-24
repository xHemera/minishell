#include "minishell.h"

int	set_input_file(t_cmd *cmd, char *file)
{
	if (cmd->input_file)
		free(cmd->input_file);
	cmd->input_file = ft_strdup(file);
	return (cmd->input_file != NULL);
}

int	set_output_file(t_cmd *cmd, char *file, int append)
{
	if (cmd->output_file)
		free(cmd->output_file);
	cmd->output_file = ft_strdup(file);
	cmd->append = append;
	return (cmd->output_file != NULL);
}

int	set_heredoc(t_cmd *cmd, char *delimiter)
{
	if (cmd->heredoc)
		free(cmd->heredoc);
	cmd->heredoc = ft_strdup(delimiter);
	return (cmd->heredoc != NULL);
}

int	test_file_access(char *file, int flags)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd == -1)
	{
		perror(file);
		return (0);
	}
	close(fd);
	return (1);
}
