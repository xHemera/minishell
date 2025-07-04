/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_and_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:40:42 by hemera            #+#    #+#             */
/*   Updated: 2025/06/30 16:47:59 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	has_syntax_error(char *line)
{
	int		i;
	int		in_quotes;
	char	quote_char;

	i = 0;
	in_quotes = 0;
	quote_char = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		return (1);
	}

	while (line[i])
	{
		// Handle quotes
		if (!in_quotes && (line[i] == '\'' || line[i] == '"'))
		{
			in_quotes = 1;
			quote_char = line[i];
		}
		else if (in_quotes && line[i] == quote_char)
		{
			in_quotes = 0;
			quote_char = 0;
		}
		else if (!in_quotes)
		{
			// Check for pipe at end or double pipes
			if (line[i] == '|')
			{
				int j = i + 1;
				while (line[j] && (line[j] == ' ' || line[j] == '\t'))
					j++;
				if (!line[j] || line[j] == '|')
				{
					ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
					return (1);
				}
			}
			// Check for redirections without arguments
			else if (line[i] == '>' || line[i] == '<')
			{
				int j = i;
				// Skip multiple redirect chars
				if (line[i] == '>' && line[i + 1] == '>' )
					j = i + 2;
				else if (line[i] == '<' && line[i + 1] == '<')
					j = i + 2;
				else if (line[i + 1] == '>' )
				{
					ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
					return (1);
				}
				else
					j = i + 1;

				// Skip whitespace after redirect
				while (line[j] && (line[j] == ' ' || line[j] == '\t'))
					j++;

				// Check if redirect is at end or followed by another redirect/pipe
				if (!line[j] || line[j] == '|' || line[j] == '>' || line[j] == '<')
				{
					if (!line[j])
						ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
					else if (line[j] == '>' )
						ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
					else if (line[j] == '<' )
						ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
					else if (line[j] == '|')
						ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
					return (1);
				}
				i = j - 1; // Will be incremented at end of loop
			}
		}
		i++;
	}
	return (0);
}

static t_cmd	*build_cmd_list(char **segments, t_env *env)
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
		cmd = parse_segment_with_env(segments[i], env);
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

	if (has_unclosed_quotes(line))
	{
		ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
		g_signal_received = 2;
		return ;
	}
	if (has_syntax_error(line))
	{
		g_signal_received = 2;
		return ;
	}
	segments = split_pipe_aware(line);
	if (!segments)
		return ;
	cmd_list = build_cmd_list(segments, *env);
	if (cmd_list)
	{
		if (!cmd_list->next)
			exec_cmd(cmd_list, env);
		else
			g_signal_received = exec_pipeline(cmd_list, env);
	}
	free_cmd_list(cmd_list);
	free_split(segments);
}
