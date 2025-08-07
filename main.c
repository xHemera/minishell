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
	t_shell shell;

	(void)argc;
	(void)argv;
	g_signal = 0;
	setup_signals();
	shell.env = env_init(envp);
	shell.cmd = NULL;
	shell.last_exit_code = 0;
	if (!shell.env)
		return (1);
	minishell_loop(&shell);
	free_env(&shell.env);
	return (shell.last_exit_code);
}
