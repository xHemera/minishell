/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:31:07 by tobesnar          #+#    #+#             */
/*   Updated: 2025/07/29 10:31:07 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_status;

void	minishell_loop(t_env **env)
{
	char	*line;

	while (1)
	{
		if (g_status == 130)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_status = 0;
		}
		line = readline("minishell> ");
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			cleanup_and_exit(0);
		}
		if (*line)
		{
			add_history(line);
			parse_and_exec(line, env);
		}
		free(line);
	}
}
