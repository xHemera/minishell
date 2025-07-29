/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:27:31 by tobesnar          #+#    #+#             */
/*   Updated: 2025/07/29 10:27:31 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g_ms = {0, NULL, NULL};

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	setup_signals();
	env = env_init(envp);
	if (!env)
		return (1);
	set_global_env(env);
	minishell_loop(&env);
	free_env(&env);
	if (g_ms.signal_received >= 130)
		return (g_ms.signal_received - 128);
	return (g_ms.signal_received);
}
