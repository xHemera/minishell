/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:17:33 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/13 11:21:05 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_cmd(t_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->argv)
		ft_free_split(cmd->argv);
	if (cmd->path)
		free(cmd->path);
}
