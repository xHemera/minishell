/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 17:37:18 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/13 17:37:33 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
	{
		printf("Commande vide\n");
		return ;
	}
	printf("Commande : %s\n", cmd->name);
	printf("Arguments :\n");
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		printf("  [%d]: %s\n", i, cmd->args[i]);
		i++;
	}
	printf("Est un builtin : %s\n", cmd->is_builtin ? "oui" : "non");
}
