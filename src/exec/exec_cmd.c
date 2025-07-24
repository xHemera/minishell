#include "minishell.h"

int	exec_cmd(t_cmd *cmd, t_env **env)
{
	if (!cmd)
		return (1);
	if (cmd->is_builtin)
		return (exec_builtin(cmd, *env));
	return (exec_external(cmd, *env));
}
