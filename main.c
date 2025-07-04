/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:55:46 by tobesnar          #+#    #+#             */
/*   Updated: 2025/06/30 17:03:04 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_received = 0;

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	setup_signals();
	env = env_init(envp);
	if (!env)
		return (1);
	minishell_loop(&env);
	free_env(&env);
	if (g_signal_received >= 130)
		return (g_signal_received - 128);
	return (g_signal_received);
}
