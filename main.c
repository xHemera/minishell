/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:53:18 by tobesnar          #+#    #+#             */
/*   Updated: 2025/06/01 12:55:15 by hemera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_str_builtin(const char *cmd, const char *name, size_t len)
{
	return (ft_strncmp(cmd, name, len) == 0
		&& (cmd[len] == '\0' || cmd[len] == ' '));
}

static int	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (is_str_builtin(cmd_name, "echo", 4))
		return (1);
	if (is_str_builtin(cmd_name, "cd", 2))
		return (1);
	if (is_str_builtin(cmd_name, "pwd", 3))
		return (1);
	if (is_str_builtin(cmd_name, "export", 6))
		return (1);
	if (is_str_builtin(cmd_name, "unset", 5))
		return (1);
	if (is_str_builtin(cmd_name, "env", 3))
		return (1);
	if (is_str_builtin(cmd_name, "exit", 4))
		return (1);
	return (0);
}

static int	exec_cmd(t_cmd *cmd, t_env **env)
{
	if (!cmd || !cmd->name)
		return (1);
	if (is_builtin(cmd->name))
		return (exec_builtin(cmd, *env));
	return (0);
}

static void	minishell_loop(t_env **env)
{
	char	*line;
	t_cmd	*cmd;

	(void)env;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			exit(0);
		if (*line)
		{
			add_history(line);
			cmd = parse_segment(line);
			if (cmd)
				exec_cmd(cmd, env);
			else
				break ;
		}
		free_cmd_list(cmd);
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	data;

	(void)argc;
	(void)argv;
	data.env = env_init(envp);
	minishell_loop(&data.env);
	free_env(&data.env);
	return (0);
}
