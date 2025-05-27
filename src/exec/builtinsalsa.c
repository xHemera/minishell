/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinsalsa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:49:20 by tlize             #+#    #+#             */
/*   Updated: 2025/05/27 18:49:37 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_cmd_args(char **args)
{
	int	count;

	count = 0;
	while (args && args[count])
		count++;
	return (count);
}

int	exec_builtin(t_cmd *cmd, t_env *envp)
{
	if (!cmd || !cmd->name)
		return (1);
	if (ft_strncmp(cmd->name, "echo", 5) == 0)
		return (ft_echo(cmd->args, 1, 2, 1));
	if (ft_strncmp(cmd->name, "export", 7) == 0)
		return (ft_export(cmd, envp));
	if (ft_strncmp(cmd->name, "env", 4) == 0)
	{
		print_env(envp);
		return (0);
	}
	if (ft_strncmp(cmd->name, "pwd", 4) == 0)
		return (ft_pwd());
	if (ft_strncmp(cmd->name, "cd", 3) == 0)
		return (ft_cd(cmd->args, envp));
	if (ft_strncmp(cmd->name, "unset", 6) == 0)
		return (ft_unset(cmd->args, envp));
	if (ft_strncmp(cmd->name, "exit", 5) == 0)
		return (ft_exit(cmd->args));
	return (1);
}
