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

extern int g_signal;

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	int exit_code;

	(void)argc;
	(void)argv;
	g_signal = 0;
	setup_signals();
	env = env_init(envp);
	if (!env)
		return (1);
	exit_code = minishell_loop(&env);
	free_env(&env);
	return (exit_code);
}
