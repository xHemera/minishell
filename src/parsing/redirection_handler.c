#include "minishell.h"

static int	set_input_file(t_cmd *cmd, char *clean_next)
{
	free(cmd->input_file);
	cmd->input_file = ft_strdup(clean_next);
	if (!cmd->input_file)
		return (0);
	free(cmd->heredoc);
	cmd->heredoc = NULL;
	return (1);
}

static int	set_heredoc(t_cmd *cmd, char *clean_next)
{
	free(cmd->heredoc);
	cmd->heredoc = ft_strdup(clean_next);
	if (!cmd->heredoc)
		return (0);
	free(cmd->input_file);
	cmd->input_file = NULL;
	return (1);
}

static int	handle_input_heredoc(t_cmd *cmd, char *token, char *next)
{
	char	*clean_next;
	int		result;
	int		test_fd;

	clean_next = remove_quotes(next);
	result = 0;

	if (!ft_strncmp(token, "<", 2))
	{
		// Tester l'accès au fichier d'entrée
		test_fd = open(clean_next, O_RDONLY);
		if (test_fd == -1)
		{
			perror(clean_next);
			free(clean_next);
			return (0);
		}
		close(test_fd);
		result = set_input_file(cmd, clean_next);
	}
	else if (!ft_strncmp(token, "<<", 3))
		result = set_heredoc(cmd, clean_next);
	free(clean_next);
	return (result);
}

static int	set_output_file(t_cmd *cmd, char *clean_next, int append)
{
	free(cmd->output_file);
	cmd->output_file = ft_strdup(clean_next);
	if (!cmd->output_file)
		return (0);
	cmd->append = append;
	return (1);
}

static int	handle_output(t_cmd *cmd, char *token, char *next)
{
	char	*clean_next;
	int		result;
	int		test_fd;
	int		flags;

	clean_next = remove_quotes(next);
	result = 0;

	// Tester l'ouverture du fichier comme bash le fait
	flags = O_WRONLY | O_CREAT;
	if (!ft_strncmp(token, ">>", 3))
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;

	test_fd = open(clean_next, flags, 0644);
	if (test_fd == -1)
	{
		perror(clean_next);
		free(clean_next);
		return (0);
	}
	close(test_fd);

	// Stocker la redirection (même si erreur, bash fait pareil)
	if (!ft_strncmp(token, ">", 2))
		result = set_output_file(cmd, clean_next, 0);
	else if (!ft_strncmp(token, ">>", 3))
		result = set_output_file(cmd, clean_next, 1);
	free(clean_next);
	return (result);
}

int	handle_redirect(t_cmd *cmd, char **tokens, int *i)
{
	if (!tokens[*i + 1])
		return (0);
	if (handle_input_heredoc(cmd, tokens[*i], tokens[*i + 1]))
	{
		*i += 2;
		return (1);
	}
	if (handle_output(cmd, tokens[*i], tokens[*i + 1]))
	{
		*i += 2;
		return (1);
	}
	return (0);
}
