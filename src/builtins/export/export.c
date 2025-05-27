/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:59:11 by tlize             #+#    #+#             */
/*   Updated: 2025/05/22 17:54:57 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//suicide garantit avant la fin de la fonction

int ft_export(t_cmd *cmd, t_env *envp)
{
	t_env	*test1;

	if (cmd->arg_count == 1)
	{
		while (envp->next)
		{
			ft_printf(envp->key);
			ft_printf("=");
			ft_printf(envp->value);
			ft_printf("\n");
			envp = envp->next;
		}
	}
	else
	{
		test1 = env_new("test", "test");
		return (1);
	}
	return (0);
}
