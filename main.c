/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:53:18 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/30 14:20:21 by hemera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (ft_strncmp(cmd_name, "echo", 4) == 0
		&& (cmd_name[4] == '\0' || cmd_name[4] == ' '))
		return (1);
	if (ft_strncmp(cmd_name, "cd", 2) == 0
		&& (cmd_name[2] == '\0' || cmd_name[2] == ' '))
		return (1);
	if (ft_strncmp(cmd_name, "pwd", 3) == 0
		&& (cmd_name[3] == '\0' || cmd_name[3] == ' '))
		return (1);
	if (ft_strncmp(cmd_name, "export", 6) == 0
		&& (cmd_name[6] == '\0' || cmd_name[6] == ' '))
		return (1);
	if (ft_strncmp(cmd_name, "unset", 5) == 0
		&& (cmd_name[5] == '\0' || cmd_name[5] == ' '))
		return (1);
	if (ft_strncmp(cmd_name, "env", 3) == 0
		&& (cmd_name[3] == '\0' || cmd_name[3] == ' '))
		return (1);
	if (ft_strncmp(cmd_name, "exit", 4) == 0
		&& (cmd_name[4] == '\0' || cmd_name[4] == ' '))
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
