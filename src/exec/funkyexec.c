/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funkyexec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:25:00 by tlize             #+#    #+#             */
/*   Updated: 2025/05/19 17:11:42 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char *envp_find(t_env *envp)
{
    while (envp->key != "PATH")
        envp = envp->next;
    return (envp->value);
}

int	exec_commande(t_cmd *cmd, t_env *envp)
{
	pid_t	pid;
	int		status;
    char    *AHOUUUUU;

	pid = fork();
    AHOUUUUU = envp_find(envp);
	if (pid < 0)
	{
		ft_putstr_fd("erreur de fork", 2);
		return (1);
	}
	if (pid == 0)
	{
		if (execve(cmd->name, cmd ->args, AHOUUUUU) == -1)
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
