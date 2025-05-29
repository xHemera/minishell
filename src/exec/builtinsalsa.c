/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinsalsa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:49:20 by tlize             #+#    #+#             */
/*   Updated: 2025/05/29 16:57:40 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_builtin(t_cmd *cmd, t_env *envp)
{
	if (!cmd || !cmd->name)
		return (1);
	if (ft_strncmp(cmd->name, "env", 3) == 0 &&
		(cmd->name[3] == '\0' || cmd->name[3] == ' '))
	{
		print_env(envp);
		return (0);
	}
	if (ft_strncmp(cmd->name, "pwd", 3) == 0 &&
		(cmd->name[3] == '\0' || cmd->name[3] == ' '))
		return (ft_pwd());
	if (ft_strncmp(cmd->name, "cd", 2) == 0 &&
		(cmd->name[2] == '\0' || cmd->name[2] == ' '))
		return (ft_cd(cmd->args, envp));
	// if (ft_strncmp(cmd->name, "unset", 5) == 0 &&
	// 	(cmd->name[5] == '\0' || cmd->name[5] == ' '))
	// 	return (ft_unset(cmd->args, &envp));
	if (ft_strncmp(cmd->name, "exit", 4) == 0 &&
		(cmd->name[4] == '\0' || cmd->name[4] == ' '))
		return (ft_exit(cmd->args));
	if (ft_strncmp(cmd->name, "echo", 4) == 0 &&
		(cmd->name[4] == '\0' || cmd->name[4] == ' '))
		return (ft_echo(cmd->args, 1, 2, 1));
	return (1);
}
