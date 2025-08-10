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

static int	execute_command_list(t_cmd *cmd_list, t_env **env)
{
	if ((!cmd_list->name) || (cmd_list->name[0] == '\0'))
		return (0);
	if (!cmd_list->next)
		return (exec_cmd(cmd_list, env));
	else
		return (exec_pipeline(cmd_list, env));
}

void	parse_and_exec(char *line, t_shell *shell)
{
	char	**segments;
	t_cmd	*cmd_list;

	if (handle_syntax_errors(line))
	{
		shell->last_exit_code = 258;
		return ;
	}
	segments = split_pipe_aware(line);
	if (!segments)
	{
		shell->last_exit_code = 1;
		return ;
	}
	cmd_list = build_cmd_list(segments, shell->env, shell->last_exit_code);
	if (cmd_list)
	{
		shell->last_exit_code = execute_command_list(cmd_list, &shell->env);
	}
	free_cmd_list(cmd_list);
	free_split(segments);
}
