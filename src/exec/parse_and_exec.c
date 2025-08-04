/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:31:12 by tobesnar          #+#    #+#             */
/*   Updated: 2025/07/29 10:31:12 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_signal;

static int	handle_syntax_errors(char *line)
{
	if (has_unclosed_quotes(line))
	{
		ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
		return (1);
	}
	if (has_syntax_error(line))
		return (1);
	return (0);
}

static void execute_command_list(t_cmd *cmd_list, t_env **env)
{
	// Skip execution if command is heredoc-only (name is empty or NULL)
	if ((!cmd_list->name) || (cmd_list->name[0] == '\0')) {
		// Still clean up, but do not execute
		return;
	}
	if (!cmd_list->next)
		g_signal =exec_cmd(cmd_list, env);
	else
		g_signal =exec_pipeline(cmd_list, env);
}

void	parse_and_exec(char *line, t_env **env)
{
	char	**segments;
	t_cmd	*cmd_list;
	int exit_code;

	exit_code = 0;
	if (handle_syntax_errors(line))
		return ;
	segments = split_pipe_aware(line);
	if (!segments)
		return ;
	cmd_list = build_cmd_list(segments, *env);
	if (cmd_list)
		execute_command_list(cmd_list, env);
	free_cmd_list(cmd_list);
	free_split(segments);
}
