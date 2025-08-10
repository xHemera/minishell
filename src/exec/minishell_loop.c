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

static void	handle_sigint_prompt(t_shell *shell)
{
	if (g_signal == 130)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		shell->last_exit_code = 130;
		g_signal = 0;
	}
}

static void	process_input_line(char *line, t_shell *shell)
{
	if (*line)
	{
		add_history(line);
		parse_and_exec(line, shell);
	}
}

int	minishell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		handle_sigint_prompt(shell);
		line = readline("minishell> ");
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			cleanup_and_exit(shell->last_exit_code);
		}
		process_input_line(line, shell);
		free(line);
	}
	return (shell->last_exit_code);
}
