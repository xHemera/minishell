/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:40:42 by hemera            #+#    #+#             */
/*   Updated: 2025/06/01 14:24:17 by hemera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_cmd	*build_cmd_list(char **segments)
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
		cmd = parse_segment(segments[i]);
		if (!cmd)
		{
			free_cmd_list(cmd_list);
			return (NULL);
		}
		if (!cmd_list)
			cmd_list = cmd;
		else
			last->next = cmd;
		last = cmd;
		i++;
	}
	return (cmd_list);
}

void	parse_and_exec(char *line, t_env **env)
{
	char	**segments;
	t_cmd	*cmd_list;

	segments = split_pipe_aware(line);
	if (!segments)
		return ;
	cmd_list = build_cmd_list(segments);
	if (cmd_list)
	{
		if (!cmd_list->next)
			exec_cmd(cmd_list, env);
		else
			exec_pipeline(cmd_list, env);
	}
	free_cmd_list(cmd_list);
	free_split(segments);
}
