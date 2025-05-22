/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinsalsa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:49:20 by tlize             #+#    #+#             */
/*   Updated: 2025/05/22 17:40:46 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int exec_builtin(t_cmd *cmd, t_env *envp)
{
    if (cmd->name == "echo")
        return (ft_echo(cmd->args, 1, 2, 1));
    if (cmd->name == "export")
        return (ft_export(cmd, envp));
    return (0);
}