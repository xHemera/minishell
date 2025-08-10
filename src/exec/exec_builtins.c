/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:29:32 by tobesnar          #+#    #+#             */
/*   Updated: 2025/07/29 10:29:32 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	save_fds(int *stdin_backup, int *stdout_backup)
{
	*stdin_backup = dup(STDIN_FILENO);
	*stdout_backup = dup(STDOUT_FILENO);
	if (*stdin_backup == -1 || *stdout_backup == -1)
		return (1);
	return (0);
}

static void	restore_fds(int stdin_backup, int stdout_backup)
{
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
}

static int	setup_builtin_redirects(t_cmd *cmd)
{
	if (cmd->input_file)
	{
		if (redirect_input(cmd) != 0)
			return (1);
	}
	if (cmd->output_file)
	{
		if (redirect_output(cmd) != 0)
			return (1);
	}
	return (0);
}

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

int	exec_builtin(t_cmd *cmd, t_env *envp, int last_exit_code)
{
	int	stdin_backup;
	int	stdout_backup;
	int	result;

	if (!cmd || !cmd->name)
		return (1);
	if (save_fds(&stdin_backup, &stdout_backup) != 0)
		return (1);
	if (setup_builtin_redirects(cmd) != 0)
	{
		restore_fds(stdin_backup, stdout_backup);
		return (1);
	}
	if (cmd->redirection_error)
	{
		restore_fds(stdin_backup, stdout_backup);
		return (1);
	}
	if (ft_strncmp(cmd->name, "pwd", 3) == 0
		&& (cmd->name[3] == '\0' || cmd->name[3] == ' '))
		result = ft_pwd();
	else if (ft_strncmp(cmd->name, "cd", 2) == 0
		&& (cmd->name[2] == '\0' || cmd->name[2] == ' '))
		result = ft_cd(cmd->args, envp);
	else if (ft_strncmp(cmd->name, "unset", 5) == 0
		&& (cmd->name[5] == '\0' || cmd->name[5] == ' '))
		result = ft_unset(cmd, envp);
	else if (ft_strncmp(cmd->name, "exit", 4) == 0
		&& (cmd->name[4] == '\0' || cmd->name[4] == ' '))
		result = ft_exit(cmd->args, last_exit_code);
	else if (ft_strncmp(cmd->name, "echo", 4) == 0
		&& (cmd->name[4] == '\0' || cmd->name[4] == ' '))
		result = ft_echo(cmd->args, 1, 2, 1);
	else if (ft_strncmp(cmd->name, "export", 6) == 0
		&& (cmd->name[6] == '\0' || cmd->name[6] == ' '))
		result = ft_export(cmd, envp, argc_super(cmd));
	else if (ft_strncmp(cmd->name, "env", 3) == 0
		&& (cmd->name[3] == '\0' || cmd->name[3] == ' '))
		result = ft_env(envp);
	else
		result = 1;
	restore_fds(stdin_backup, stdout_backup);
	return (result);
}
