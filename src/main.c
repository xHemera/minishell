/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:19:54 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/27 19:15:58 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	is_builtin(char *cmd_name)
{
	if (!cmd_name)
		return (0);
	if (ft_strncmp(cmd_name, "echo", 4) == 0 &&
		(cmd_name[4] == '\0' || cmd_name[4] == ' '))
		return (1);
	if (ft_strncmp(cmd_name, "cd", 2) == 0 &&
		(cmd_name[2] == '\0' || cmd_name[2] == ' '))
		return (1);
	if (ft_strncmp(cmd_name, "pwd", 3) == 0 &&
		(cmd_name[3] == '\0' || cmd_name[3] == ' '))
		return (1);
	if (ft_strncmp(cmd_name, "export", 6) == 0 &&
		(cmd_name[6] == '\0' || cmd_name[6] == ' '))
		return (1);
	if (ft_strncmp(cmd_name, "unset", 5) == 0 &&
		(cmd_name[5] == '\0' || cmd_name[5] == ' '))
		return (1);
	if (ft_strncmp(cmd_name, "env", 3) == 0 &&
		(cmd_name[3] == '\0' || cmd_name[3] == ' '))
		return (1);
	if (ft_strncmp(cmd_name, "exit", 4) == 0 &&
		(cmd_name[4] == '\0' || cmd_name[4] == ' '))
		return (1);
	return (0);
}

static int	execute_command(t_cmd *cmd, t_env **env)
{
	if (!cmd || !cmd->name)
		return (1);
	if (is_builtin(cmd->name))
		return (exec_builtin(cmd, *env));
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*prompt;
	t_env	*env;
	t_cmd	*cmd_list;
	int		exit_status;

	(void)argc;
	(void)argv;
	env = env_init(envp);
	if (!env)
		return (1);
	exit_status = 0;
	while (1)
	{
		prompt = get_prompt();
		line = readline(prompt);
		free(prompt);
		if (!line)
			break ;
		if (ft_strlen(line) > 0)
		{
			add_history(line);
			cmd_list = parse_line(line);
			if (cmd_list)
			{
				exit_status = execute_command(cmd_list, &env);
				cmd_list_clear(&cmd_list);
			}
		}
		free(line);
	}
	env_clear(&env);
	return (exit_status);
}
