/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/10 10:33:22 by tobesnar          #+#    #+#             */
/*   Updated: 2025/08/10 19:49:01 by hemera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	setup_output_flags(char *token)
{
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (!ft_strncmp(token, ">>", 3))
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	return (flags);
}

int	set_output_redirect(t_cmd *cmd, char *token, char *clean_next)
{
	int	result;

	if (!ft_strncmp(token, ">", 2))
		result = set_output_file(cmd, clean_next, 0);
	else if (!ft_strncmp(token, ">>", 3))
		result = set_output_file(cmd, clean_next, 1);
	else
		result = 0;
	if (!result)
		perror(clean_next);
	return (result);
}
