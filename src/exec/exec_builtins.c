/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:13:31 by hemera            #+#    #+#             */
/*   Updated: 2025/06/01 13:09:03 by hemera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	argc_super(t_cmd *cmd)
// {
//     int i;

//     i = 0;
// 	while (cmd->args[i])
// 		i ++;
// 	return (i);
// }

int	exec_builtin(t_cmd *cmd, t_env *envp)
{
	if (!cmd || !cmd->name)
		return (1);
	// if (ft_strncmp(cmd->name, "env", 3) == 0 &&
	// 	(cmd->name[3] == '\0' || cmd->name[3] == ' '))
	// {
	// 	print_env(envp);
	// 	return (0);
	// }
	if (ft_strncmp(cmd->name, "pwd", 3) == 0 &&
		(cmd->name[3] == '\0' || cmd->name[3] == ' '))
		return (ft_pwd());
	if (ft_strncmp(cmd->name, "cd", 2) == 0 &&
		(cmd->name[2] == '\0' || cmd->name[2] == ' '))
		return (ft_cd(cmd->args, envp));
	// if (ft_strncmp(cmd->name, "unset", 5) == 0 &&
	// 	(cmd->name[5] == '\0' || cmd->name[5] == ' '))
	// 	return (ft_unset(cmd->args, &envp));
	if (ft_strncmp(cmd->name, "exit", 4) == 0 &&
		(cmd->name[4] == '\0' || cmd->name[4] == ' '))
		return (ft_exit(cmd->args));
	if (ft_strncmp(cmd->name, "echo", 4) == 0 &&
		(cmd->name[4] == '\0' || cmd->name[4] == ' '))
		return (ft_echo(cmd->args, 1, 2, 1));
	// if (ft_strncmp(cmd->name, "export", 6) == 0 &&
	// 	(cmd->name[6] == '\0' || cmd->name[6] == ' '))
	// 	return (ft_export(cmd, envp, argc_super(cmd)));
	return (1);
}

int	exec_external(t_cmd *cmd, t_env *env)
{
	pid_t	pid;
	int		status;
	char	**envp;

	envp = env_to_array(env); // Fonction à implémenter si elle n'existe pas

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (1);
	}
	if (pid == 0)
	{
		execve(cmd->name, cmd->args, envp);
		perror("execve");
		exit(127);
	}
	waitpid(pid, &status, 0);
	free_split(envp);
	return (WEXITSTATUS(status));
}
