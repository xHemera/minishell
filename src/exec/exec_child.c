/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 13:47:22 by tlize             #+#    #+#             */
/*   Updated: 2025/06/30 14:31:07 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_heredoc_file(t_cmd *cmd)
{
	char	*line;
	int		fd;

	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (perror(".heredoc_tmp"), 0);
	while (1)
	{
		write(1, "> ", 2);
		line = get_next_line(0);
		if (!line)
			break ;
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
	return (1);
}

static int	redirect_heredoc(t_cmd *cmd, int fd)
{
	if (!create_heredoc_file(cmd))
		perror("heredoc");
	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd != -1)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		unlink(".heredoc_tmp");
	}
	else
		perror("heredoc");
	return (fd);
}

static void	redirect_input(t_cmd *cmd)
{
	int	fd;

	fd = -1;
	if (cmd->heredoc)
		redirect_heredoc(cmd, fd);
	else if (cmd->input_file)
	{
		fd = open(cmd->input_file, O_RDONLY);
		if (fd != -1)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
		else
			perror(cmd->input_file);
	}
}

static void	redirect_output(t_cmd *cmd)
{
	int	fd;
	int	flags;

	fd = -1;
	flags = O_WRONLY | O_CREAT;
	if (cmd->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	if (cmd->output_file)
	{
		fd = open(cmd->output_file, flags, 0644);
		if (fd != -1)
		{
			dup2(fd, STDOUT_FILENO);
			close(fd);
		}
		else
			perror(cmd->output_file);
	}
}

int	exec_child(t_cmd *cmd, char **envp, t_env *env)
{
	redirect_input(cmd);
	redirect_output(cmd);
	if (access(cmd->name, F_OK) == 0)
		execve(cmd->name, cmd->args, envp);
	else
		execve(get_path(cmd, env, -1), cmd->args, envp);
	perror("execve");
	free_split(envp);
	exit(127);
}
