/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:00:00 by hemera            #+#    #+#             */
/*   Updated: 2024/12/19 14:00:00 by hemera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_heredoc_file(t_cmd *cmd)
{
	if (cmd->heredoc)
	{
		free(cmd->heredoc);
		cmd->heredoc = NULL;
	}
}
