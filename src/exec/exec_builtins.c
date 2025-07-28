/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:42:32 by marvin            #+#    #+#             */
/*   Updated: 2025/07/24 21:42:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	argc_super(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
		i++;
	return (i);
}

int	is_str_builtin(const char *cmd, const char *name, size_t len)
{
	return (ft_strncmp(cmd, name, len) == 0
		&& (cmd[len] == '\0' || cmd[len] == ' '));
}

int	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	return (is_str_builtin(cmd_name, "echo", 4)
		|| is_str_builtin(cmd_name, "cd", 2)
		|| is_str_builtin(cmd_name, "pwd", 3)
		|| is_str_builtin(cmd_name, "export", 6)
		|| is_str_builtin(cmd_name, "unset", 5)
		|| is_str_builtin(cmd_name, "env", 3)
		|| is_str_builtin(cmd_name, "exit", 4));
}

int	exec_builtin(t_cmd *cmd, t_env *envp)
{
	if (!cmd || !cmd->name)
		return (1);
	if (ft_strncmp(cmd->name, "pwd", 3) == 0
		&& (cmd->name[3] == '\0' || cmd->name[3] == ' '))
		return (ft_pwd());
	if (ft_strncmp(cmd->name, "cd", 2) == 0
		&& (cmd->name[2] == '\0' || cmd->name[2] == ' '))
		return (ft_cd(cmd->args, envp));
	if (ft_strncmp(cmd->name, "unset", 5) == 0
		&& (cmd->name[5] == '\0' || cmd->name[5] == ' '))
		return (ft_unset(cmd, envp));
	if (ft_strncmp(cmd->name, "exit", 4) == 0
		&& (cmd->name[4] == '\0' || cmd->name[4] == ' '))
		return (ft_exit(cmd->args));
	if (ft_strncmp(cmd->name, "echo", 4) == 0
		&& (cmd->name[4] == '\0' || cmd->name[4] == ' '))
		return (ft_echo(cmd->args, 1, 2, 1));
	if (ft_strncmp(cmd->name, "export", 6) == 0
		&& (cmd->name[6] == '\0' || cmd->name[6] == ' '))
		return (ft_export(cmd, envp, argc_super(cmd)));
	if (ft_strncmp(cmd->name, "env", 3) == 0
		&& (cmd->name[3] == '\0' || cmd->name[3] == ' '))
		return (ft_env(envp));
	return (1);
}
