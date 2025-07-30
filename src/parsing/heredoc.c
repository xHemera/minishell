#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

// Crée le fichier temporaire et lit jusqu'au délimiteur
int handle_heredoc(t_cmd *cmd)
{
	char *line = NULL;
	int fd;

	if (!cmd->heredoc)
		return (0);
	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("heredoc");
		return (1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || (!ft_strncmp(line, cmd->heredoc, ft_strlen(cmd->heredoc)) && (line[ft_strlen(cmd->heredoc)] == '\0')))
		{
			free(line);
			break;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
	return (0);
}

// Redirige STDIN sur le fichier temporaire
int redirect_heredoc_input(void)
{
	int fd = open(".heredoc_tmp", O_RDONLY);
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
