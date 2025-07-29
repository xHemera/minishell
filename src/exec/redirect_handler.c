/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:31:16 by tobesnar          #+#    #+#             */
/*   Updated: 2025/07/29 10:31:16 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_heredoc_line(char *line, t_cmd *cmd, int fd)
{
	if (!line)
	{
		if (g_ms.signal_received == SIGINT)
		{
			close(fd);
			unlink(".heredoc_tmp");
			exit(130);
		}
		return (0);
	}
	if (!ft_strncmp(line, cmd->heredoc, ft_strlen(cmd->heredoc))
		&& line[ft_strlen(cmd->heredoc)] == '\n')
	{
		free(line);
		return (0);
	}
	write(fd, line, ft_strlen(line));
	free(line);
	return (1);
}

int	create_heredoc_file(t_cmd *cmd)
{
	char	*line;
	int		fd;

	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror(".heredoc_tmp");
		return (0);
	}
	setup_signals_heredoc();
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!handle_heredoc_line(line, cmd, fd))
			break ;
	}
	close(fd);
	setup_signals_child();
	return (1);
}
