/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:30:48 by tobesnar          #+#    #+#             */
/*   Updated: 2025/07/29 10:30:48 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent_process_cleanup(t_cmd *cmd, int pipe_fd[2], int *in_fd)
{
	if (cmd->next)
	{
		close(pipe_fd[1]);
		if (*in_fd != STDIN_FILENO)
			close(*in_fd);
		*in_fd = pipe_fd[0];
	}
}
