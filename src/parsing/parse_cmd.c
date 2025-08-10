/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:00:00 by hemera            #+#    #+#             */
/*   Updated: 2024/12/19 14:00:00 by hemera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_tokens_with_expansion(t_cmd *cmd, char **tokens, t_env *env)
{
	int	i;
	int	has_command;

	i = 0;
	has_command = 0;
	while (tokens[i])
	{
		if (is_redirect(tokens[i]))
		{
			if (!handle_redirect(cmd, tokens, &i))
				return (0);
			continue ;
		}
		else
		{
			if (!handle_token(cmd, tokens[i], !has_command, env))
				return (0);
			if (!has_command && cmd->name && cmd->name[0] != '\0')
				has_command = 1;
			i++;
		}
	}
	return (1);
}

static int	setup_empty_command(t_cmd *cmd)
{
	if (cmd->heredoc && !cmd->name)
	{
		cmd->name = ft_strdup("");
		if (!cmd->name)
			return (0);
	}
	return (1);
}

static int	handle_parsed_tokens(t_cmd *cmd, char **tokens, t_env *env)
{
	int	success;

	success = parse_tokens_with_expansion(cmd, tokens, env);
	free_tokens(tokens);
	if (!success)
		return (0);
	if (!setup_empty_command(cmd))
		return (0);
	return (1);
}

t_cmd	*parse_segment_with_env(char *segment, t_env *env, int last_exit_code)
{
	t_cmd	*cmd;
	char	**tokens;

	cmd = cmd_new();
	if (!cmd)
		return (NULL);
	cmd->last_exit_code = last_exit_code;
	tokens = tokenize_improved(segment);
	if (!tokens)
	{
		free_cmd(cmd);
		return (NULL);
	}
	if (!handle_parsed_tokens(cmd, tokens, env))
	{
		free_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}
