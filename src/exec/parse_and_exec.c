/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:44:20 by marvin            #+#    #+#             */
/*   Updated: 2025/07/24 21:44:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_syntax_errors(char *line)
{
	if (has_unclosed_quotes(line))
	{
		ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
		g_ms.signal_received = 2;
		return (1);
	}
	if (has_syntax_error(line))
	{
		g_ms.signal_received = 2;
		return (1);
	}
	return (0);
}

static void	execute_command_list(t_cmd *cmd_list, t_env **env)
{
	if (!cmd_list->next)
		g_ms.signal_received = exec_cmd(cmd_list, env);
	else
		g_ms.signal_received = exec_pipeline(cmd_list, env);
}

void	parse_and_exec(char *line, t_env **env)
{
	char	**segments;
	t_cmd	*cmd_list;

	if (handle_syntax_errors(line))
		return ;
	segments = split_pipe_aware(line);
	if (!segments)
		return ;
	cmd_list = build_cmd_list(segments, *env);
	set_global_cmd(cmd_list);
	if (cmd_list)
		execute_command_list(cmd_list, env);
	else
		g_ms.signal_received = 1;
	free_cmd_list(cmd_list);
	set_global_cmd(NULL);
	free_split(segments);
}
