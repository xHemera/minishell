/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:33:17 by tobesnar          #+#    #+#             */
/*   Updated: 2025/07/29 10:33:17 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_redirect(t_cmd *cmd, char **tokens, int *i)
{
	char	*token;
	char	*next;
	int		result;

	token = tokens[*i];
	next = tokens[*i + 1];
	if (!next)
		return (0);
	if (cmd->redirection_error)
	{
		(*i) += 2;
		return (1);
	}
	if (token[0] == '<')
		result = handle_input_redirect(cmd, token, next);
	else
		result = handle_output_redirect(cmd, token, next);
	(*i) += 2;
	if (!result)
		cmd->redirection_error = 1;
	return (1);
}
