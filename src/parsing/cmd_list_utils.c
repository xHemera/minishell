/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:31:24 by tobesnar          #+#    #+#             */
/*   Updated: 2025/07/29 10:31:24 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_cmd_to_list(t_cmd **cmd_list, t_cmd **last, t_cmd *cmd)
{
	if (!*cmd_list)
		*cmd_list = cmd;
	else
		(*last)->next = cmd;
	*last = cmd;
}

t_cmd	*build_cmd_list(char **segments, t_env *env, int last_exit_code)
{
	t_cmd	*cmd_list;
	t_cmd	*last;
	t_cmd	*cmd;
	int		i;

	cmd_list = NULL;
	last = NULL;
	i = 0;
	while (segments[i])
	{
		cmd = parse_segment_with_env(segments[i], env, last_exit_code);
		if (!cmd)
		{
			free_cmd_list(cmd_list);
			return (NULL);
		}
		add_cmd_to_list(&cmd_list, &last, cmd);
		i++;
	}
	return (cmd_list);
}
