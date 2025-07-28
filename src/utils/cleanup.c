/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:46:52 by marvin            #+#    #+#             */
/*   Updated: 2025/07/24 21:46:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	set_global_env(t_env *env)
{
	g_ms.env_ptr = env;
}

void	set_global_cmd(t_cmd *cmd)
{
	g_ms.cmd_ptr = cmd;
}

void	cleanup_and_exit(int exit_code)
{
	if (g_ms.cmd_ptr)
	{
		free_cmd_list(g_ms.cmd_ptr);
		g_ms.cmd_ptr = NULL;
	}
	if (g_ms.env_ptr)
	{
		free_env(&g_ms.env_ptr);
		g_ms.env_ptr = NULL;
	}
	exit(exit_code);
}
