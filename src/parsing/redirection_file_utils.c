/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_file_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:32:48 by tobesnar          #+#    #+#             */
/*   Updated: 2025/07/29 10:32:48 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_input_file(t_cmd *cmd, char *file)
{
	if (cmd->input_file)
		free(cmd->input_file);
	cmd->input_file = ft_strdup(file);
	return (cmd->input_file != NULL);
}

int	set_output_file(t_cmd *cmd, char *file, int append)
{
	if (cmd->output_file)
		free(cmd->output_file);
	cmd->output_file = ft_strdup(file);
	cmd->append = append;
	return (cmd->output_file != NULL);
}


int	test_file_access(char *file, int flags)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd == -1)
	{
		perror(file);
		return (0);
	}
	close(fd);
	return (1);
}
