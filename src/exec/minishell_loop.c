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

void	minishell_loop(t_env **env)
{
	char	*line;

	while (1)
	{
		if (g_ms.last_was_signaled)
		{
			write(1, "\n", 1);
			g_ms.last_was_signaled = 0;
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
