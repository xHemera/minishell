/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:32:21 by tobesnar          #+#    #+#             */
/*   Updated: 2025/07/29 11:12:45 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_expanded_token(char *token, t_env *env, int last_exit_code)
{
	char	*expanded_token;

	expanded_token = ft_expand_variables_quotes(token, env, last_exit_code);
	if (!expanded_token)
	{
		expanded_token = ft_strdup(token);
		if (!expanded_token)
			return (NULL);
	}
	return (expanded_token);
}

int	setup_empty_cmd(t_cmd *cmd)
{
	cmd->name = ft_strdup("");
	if (!cmd->name)
		return (0);
	cmd->args = malloc(sizeof(char *) * 2);
	if (!cmd->args)
	{
		free(cmd->name);
		cmd->name = NULL;
		return (0);
	}
	cmd->args[0] = ft_strdup("");
	if (!cmd->args[0])
	{
		free(cmd->args);
		free(cmd->name);
		cmd->name = NULL;
		cmd->args = NULL;
		return (0);
	}
	cmd->args[1] = NULL;
	return (1);
}

static int	handle_first_token(t_cmd *cmd, char *expanded_token)
{
	if (expanded_token[0] == '\0')
		return (1);
	cmd->is_builtin = is_builtin(expanded_token);
	return (add_arg_or_name(cmd, expanded_token));
}

int	handle_token(t_cmd *cmd, char *token, int is_first, t_env *env)
{
	char	*expanded_token;
	int		result;

	expanded_token = get_expanded_token(token, env, cmd->last_exit_code);
	if (!expanded_token)
		return (0);
	if (expanded_token[0] == '\0')
	{
		free(expanded_token);
		return (1);
	}
	if (is_first)
		result = handle_first_token(cmd, expanded_token);
	else
		result = add_arg_or_name(cmd, expanded_token);
	free(expanded_token);
	return (result);
}
