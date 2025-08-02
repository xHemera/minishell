/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:30:18 by tobesnar          #+#    #+#             */
/*   Updated: 2025/07/29 10:30:18 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_cmd *cmd, t_env **env)
{
	if (!cmd)
		return (1);
	// Guard: skip execution if name is NULL or empty (heredoc-only or invalid command)
	if (!cmd->name || cmd->name[0] == '\0')
		return (0);
	if (cmd->is_builtin)
		return (exec_builtin(cmd, *env));
	return (exec_external(cmd, *env));
}
