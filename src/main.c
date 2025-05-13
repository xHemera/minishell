/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:19:54 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/13 17:38:57 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*prompt;
	t_env	*env;
	t_cmd	*cmd_list;

	(void)argc;
	(void)argv;
	env = env_init(envp);
	if (!env)
		return (1);
	while (1)
	{
		prompt = get_prompt();
		line = readline(prompt);
		free(prompt);
		if (!line)
			break ;
		add_history(line);
		if (!handle_builtin(line, env))
		{
			cmd_list = parse_line(line);
			if (cmd_list)
				print_cmd(cmd_list);
			cmd_list_clear(&cmd_list);
		}
		free(line);
	}
	env_clear(&env);
	return (0);
}
