#include "../../include/minishell.h"

static t_env	*g_env_ptr = NULL;

void	set_global_env(t_env *env)
{
	g_env_ptr = env;
}

void	cleanup_and_exit(int exit_code)
{
	if (g_env_ptr)
		free_env(&g_env_ptr);
	exit(exit_code);
}
