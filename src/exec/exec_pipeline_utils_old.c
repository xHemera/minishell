/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:29:13 by hemera            #+#    #+#             */
/*   Updated: 2025/06/01 14:31:07 by hemera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_process_cleanup(t_cmd *cmd, int pipe_fd[2], int *in_fd)
{
	if (*in_fd != 0)
		close(*in_fd);
	if (cmd->next)
	{
		close(pipe_fd[1]);
		*in_fd = pipe_fd[0];
	}
}

void	launch_child_process(t_cmd *cmd, int pipe_fd[2],
		int in_fd, t_env **env)
{
	// Dans un pipeline, nous sommes déjà dans un processus enfant
	if (is_builtin(cmd->name))
	{
		// Gestion des redirections pour les builtins
		if (cmd->input_file || cmd->output_file || cmd->append || cmd->heredoc)
		{
			redirect_input(cmd);
			redirect_output(cmd);
		}

		// Redirections du pipeline après les redirections de fichiers
		if (cmd->next)
			dup2(pipe_fd[1], 1);
		if (in_fd != 0)
			dup2(in_fd, 0);
		if (cmd->next)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}

		int exit_code = exec_builtin(cmd, *env);
		exit(exit_code);
	}
	else
	{
		// Pour les commandes externes, nous devons faire les redirections dans le bon ordre
		// 1. Redirections de fichiers d'abord
		redirect_input(cmd);
		redirect_output(cmd);

		// 2. Redirections du pipeline ensuite
		if (cmd->next)
			dup2(pipe_fd[1], 1);
		if (in_fd != 0)
			dup2(in_fd, 0);
		if (cmd->next)
		{
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}

		// 3. Exécution de la commande
		char **envp = env_to_array(*env);
		if (!envp)
			exit(1);
		setup_signals_child();
		if (access(cmd->name, F_OK) == 0)
			execve(cmd->name, cmd->args, envp);
		else
			execve(get_path(cmd, *env, -1), cmd->args, envp);
		perror("execve");
		free_split(envp);
		exit(127);
	}
}
