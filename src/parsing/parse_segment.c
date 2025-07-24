/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_segment.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:45:53 by marvin            #+#    #+#             */
/*   Updated: 2025/07/24 21:45:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	parse_tokens(t_cmd *cmd, char **tokens)
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
		if (!add_arg_or_name(cmd, tokens[i]))
			return (0);
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
