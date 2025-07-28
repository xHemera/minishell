/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:42:45 by marvin            #+#    #+#             */
/*   Updated: 2025/07/24 21:42:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_cmd(t_cmd *cmd, t_env **env)
{
	if (!cmd)
		return (1);
	if (cmd->is_builtin)
		return (exec_builtin(cmd, *env));
	return (exec_external(cmd, *env));
}
