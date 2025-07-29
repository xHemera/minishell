/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:34:25 by tobesnar          #+#    #+#             */
/*   Updated: 2025/07/29 10:34:25 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
