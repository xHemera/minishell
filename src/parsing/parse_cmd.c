/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:45:47 by marvin            #+#    #+#             */
/*   Updated: 2025/07/24 21:45:47 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_tokens_with_expansion(t_cmd *cmd, char **tokens, t_env *env)
{
	int		i;

	i = 0;
	while (tokens[i])
	{
		if (is_redirect(tokens[i]))
		{
			if (!handle_redirect(cmd, tokens, &i))
				return (0);
			continue ;
		}
		if (!handle_token(cmd, tokens[i], i == 0, env))
			return (0);
		i++;
	}
	return (1);
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
