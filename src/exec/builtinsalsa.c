/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinsalsa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:49:20 by tlize             #+#    #+#             */
/*   Updated: 2025/05/22 17:38:01 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int exec_builtin(t_cmd *cmd, t_env *envp)
{
    if (cmd->name == "echo")
        return (ft_echo(cmd->args, 1, 2, 1));
    if (cmd->name == "export")
        return (ft_export(envp, cmd->arg_count));
    return (0);
}