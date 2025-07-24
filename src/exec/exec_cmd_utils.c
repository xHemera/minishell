#include "minishell.h"

static void	handle_command_not_found(char *cmd_name)
{
	write(2, cmd_name, ft_strlen(cmd_name));
	write(2, ": command not found\n", 20);
	exit(127);
}

static void	handle_execution_error(char *cmd_name)
{
	perror(cmd_name);
	exit(127);
}

void	execute_command(t_cmd *cmd, char **envp, t_env *env)
{
	char	*path;

	if (ft_strchr(cmd->name, '/') || cmd->name[0] == '.')
	{
		if (access(cmd->name, F_OK) == 0)
		{
			if (execve(cmd->name, cmd->args, envp) == -1)
				handle_execution_error(cmd->name);
		}
		else
			handle_execution_error(cmd->name);
	}
	else
	{
		path = get_path(cmd, env);
		if (path)
		{
			if (execve(path, cmd->args, envp) == -1)
				handle_execution_error(cmd->name);
		}
		else
			handle_command_not_found(cmd->name);
	}
}
