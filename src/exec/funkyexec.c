/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funkyexec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:25:00 by tlize             #+#    #+#             */
/*   Updated: 2025/05/13 12:01:02 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_commande(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("erreur de fork", 2);
		return (1);
	}
	if (pid == 0)
	{
		if (execve(cmd->path, cmd ->argv, envp) == -1)
		{
			ft_putstr_fd("erreur de execve", 2);
			exit(127);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			ft_putstr_fd("erreur de waitpid", 2);
			return (1);
		}
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (128 + WTERMSIG(status));
	}
	return (1);
}
