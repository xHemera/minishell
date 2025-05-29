/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:59:11 by tlize             #+#    #+#             */
/*   Updated: 2025/05/29 11:55:04 by hemera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	ft_export(t_cmd *cmd, t_env *envp)
{
	if (cmd->arg_count == 1)
	{
		while (envp)
		{
			ft_printf("%s=%s\n", envp->key, envp->value);
			envp = envp->next;
		}
	}
	else
	{
		/* TODO: gérer l'ajout ou la modification de variables d'environnement */
		ft_putstr_fd("export: variable export not implemented\n", 2);
		return (1);
	}
	return (0);
}
