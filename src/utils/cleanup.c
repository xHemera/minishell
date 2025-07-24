#include "../../include/minishell.h"

static t_env	*g_env_ptr = NULL;
static t_cmd	*g_cmd_ptr = NULL;

void	set_global_env(t_env *env)
{
	g_env_ptr = env;
}

void	set_global_cmd(t_cmd *cmd)
{
	g_cmd_ptr = cmd;
}

void	cleanup_and_exit(int exit_code)
{
	if (g_cmd_ptr)
	{
		free_cmd_list(g_cmd_ptr);
		g_cmd_ptr = NULL;
	}
	if (g_env_ptr)
	{
		free_env(&g_env_ptr);
		g_env_ptr = NULL;
	}
	exit(exit_code);
}
