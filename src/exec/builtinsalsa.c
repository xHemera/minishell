/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinsalsa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 16:49:20 by tlize             #+#    #+#             */
/*   Updated: 2025/05/22 18:19:37 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	argc_super(t_cmd *cmd)
{
    int i;

    i = 0;
	while (cmd->args[i])
		i ++;
	return (i);
}

int exec_builtin(t_cmd *cmd, t_env *envp)
{
	int nasdas;

	nasdas = argc_super(cmd);
    if (cmd->name == "echo")
        return (ft_echo(cmd->args, 1, 2, 1));
    if (cmd->name == "export")
        return (ft_export(cmd, envp, nasdas));
    return (0);
}