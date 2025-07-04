/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 17:20:46 by tobesnar          #+#    #+#             */
/*   Updated: 2025/06/30 16:58:27 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirect(const char *token)
{
	if (!token)
		return (0);
	if (!ft_strncmp(token, "<", 2) || !ft_strncmp(token, ">", 2)
		|| !ft_strncmp(token, ">>", 3) || !ft_strncmp(token, "<<", 3))
		return (1);
	return (0);
}

static void	add_arg_or_name(t_cmd *cmd, char *token)
{
	char	*clean_token;

	clean_token = remove_quotes(token);
	if (!clean_token || clean_token[0] == '\0')
	{
		free(clean_token);
		return;
	}

	if (!cmd->name)
	{
		cmd->name = ft_strdup(clean_token);
		cmd_add_arg(cmd, ft_strdup(clean_token));
	}
	else
		cmd_add_arg(cmd, ft_strdup(clean_token));
	free(clean_token);
}

static int	parse_tokens(t_cmd *cmd, char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (is_redirect(tokens[i]))
		{
			if (!handle_redirect(cmd, tokens, &i))
				return (0);
			continue ;
		}
		add_arg_or_name(cmd, tokens[i]);
		i++;
	}
	return (1);
}

static int	parse_tokens_with_expansion(t_cmd *cmd, char **tokens, t_env *env)
{
	int		i;
	char	*expanded_token;

	i = 0;
	while (tokens[i])
	{
		if (is_redirect(tokens[i]))
		{
			if (!handle_redirect(cmd, tokens, &i))
				return (0);
			continue ;
		}
		expanded_token = ft_expand_variables_quotes(tokens[i], env, g_signal_received);
		if (!expanded_token)
		{
			expanded_token = ft_strdup(tokens[i]);
			if (!expanded_token)
				return (0);
		}
		add_arg_or_name(cmd, expanded_token);
		free(expanded_token);
		i++;
	}
	return (1);
}

t_cmd	*parse_segment(char *segment)
{
	t_cmd	*cmd;
	char	**tokens;
	int		success;

	cmd = cmd_new();
	if (!cmd)
		return (NULL);
	tokens = tokenize_improved(segment);
	if (!tokens)
	{
		free_cmd(cmd);
		return (NULL);
	}
	success = parse_tokens(cmd, tokens);
	free_tokens(tokens);
	if (!success)
	{
		free_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}

t_cmd	*parse_segment_with_env(char *segment, t_env *env)
{
	t_cmd	*cmd;
	char	**tokens;
	int		success;

	cmd = cmd_new();
	if (!cmd)
		return (NULL);
	tokens = tokenize_improved(segment);
	if (!tokens)
	{
		free_cmd(cmd);
		return (NULL);
	}
	success = parse_tokens_with_expansion(cmd, tokens, env);
	free_tokens(tokens);
	if (!success)
	{
		free_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}
