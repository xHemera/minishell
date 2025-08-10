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
	if (!cmd->name || cmd->name[0] == '\0')
		return (0);
	if (cmd->is_builtin)
		return (exec_builtin(cmd, *env, cmd->last_exit_code));
	return (exec_external(cmd, *env));
}
