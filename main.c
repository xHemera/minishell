/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:53:18 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/29 17:59:34 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			{
				print_cmd_list(cmd);
				free_cmd_list(cmd);
			}
			else
				ft_printf("Parse error\n");
		}
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
