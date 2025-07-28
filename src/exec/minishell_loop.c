/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:44:15 by marvin            #+#    #+#             */
/*   Updated: 2025/07/24 21:44:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(t_env **env)
{
	char	*line;

	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			if (g_ms.signal_received >= 130)
				cleanup_and_exit(g_ms.signal_received - 128);
			cleanup_and_exit(g_ms.signal_received);
		}
		if (g_ms.signal_received == 130)
		{
			g_ms.signal_received = 0;
		}
		if (*line)
		{
			add_history(line);
			parse_and_exec(line, env);
		}
		free(line);
	}
}
