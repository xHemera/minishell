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
			if (g_signal_received >= 130)
				cleanup_and_exit(g_signal_received - 128);
			cleanup_and_exit(g_signal_received);
		}
		if (g_signal_received == 130)
		{
			g_signal_received = 0;
		}
		if (*line)
		{
			add_history(line);
			parse_and_exec(line, env);
		}
		free(line);
	}
}
