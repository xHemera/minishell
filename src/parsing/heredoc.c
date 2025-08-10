/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:00:00 by hemera            #+#    #+#             */
/*   Updated: 2024/12/19 14:00:00 by hemera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	write_line_to_fd(int fd, char *line)
{
	write(fd, line, ft_strlen(line));
	write(fd, "\n", 1);
	return (0);
}

static int	check_delimiter(char *line, char *delimiter)
{
	if (!line)
		return (1);
	if (!ft_strncmp(line, delimiter, ft_strlen(delimiter))
		&& (line[ft_strlen(delimiter)] == '\0'))
		return (1);
	return (0);
}

static int	read_heredoc_lines(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (check_delimiter(line, delimiter))
		{
			free(line);
			break ;
		}
		write_line_to_fd(fd, line);
		free(line);
	}
	return (0);
}

int	handle_heredoc(t_cmd *cmd)
{
	int	fd;

	if (!cmd->heredoc)
		return (0);
	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror("heredoc");
		return (1);
	}
	read_heredoc_lines(fd, cmd->heredoc);
	close(fd);
	return (0);
}

int	redirect_heredoc_input(void)
{
	int	fd;

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
