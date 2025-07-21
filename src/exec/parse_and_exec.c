#include "minishell.h"

static int	check_pipe_errors(char *line, int i)
{
	int	j;

	if (line[i] == '|')
	{
		j = i + 1;
		while (line[j] && (line[j] == ' ' || line[j] == '\t'))
			j++;
		if (!line[j] || line[j] == '|')
		{
			ft_putstr_fd("minishell: syntax error near unexpected ", 2);
			ft_putstr_fd("token `|'\n", 2);
			return (1);
		}
	}
	return (0);
}

static int	check_redirect_errors(char *line, int *i)
{
	int	j;

	if (line[*i] == '>' || line[*i] == '<')
	{
		j = *i;
		if (line[*i] == '>' && line[*i + 1] == '>')
			j = *i + 2;
		else if (line[*i] == '<' && line[*i + 1] == '<')
			j = *i + 2;
		else if (line[*i + 1] == '>')
		{
			ft_putstr_fd("minishell: syntax error near unexpected ", 2);
			ft_putstr_fd("token `>'\n", 2);
			return (1);
		}
		else
			j = *i + 1;
		while (line[j] && (line[j] == ' ' || line[j] == '\t'))
			j++;
		if (!line[j] || line[j] == '|' || line[j] == '>' || line[j] == '<')
		{
			if (!line[j])
				ft_putstr_fd("minishell: syntax error near unexpected "
					"token `newline'\n", 2);
			else if (line[j] == '>')
				ft_putstr_fd("minishell: syntax error near unexpected "
					"token `>'\n", 2);
			else if (line[j] == '<')
				ft_putstr_fd("minishell: syntax error near unexpected "
					"token `<'\n", 2);
			else if (line[j] == '|')
				ft_putstr_fd("minishell: syntax error near unexpected "
					"token `|'\n", 2);
			return (1);
		}
		*i = j - 1;
	}
	return (0);
}

static int	check_initial_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	if (line[i] == '|')
	{
		ft_putstr_fd("minishell: syntax error near unexpected ", 2);
		ft_putstr_fd("token `|'\n", 2);
		return (1);
	}
	return (0);
}

static void	handle_quotes(char c, int *in_quotes, char *quote_char)
{
	if (!*in_quotes && (c == '\'' || c == '"'))
	{
		*in_quotes = 1;
		*quote_char = c;
	}
	else if (*in_quotes && c == *quote_char)
	{
		*in_quotes = 0;
		*quote_char = 0;
	}
}

static int	has_syntax_error(char *line)
{
	int		i;
	int		in_quotes;
	char	quote_char;

	if (check_initial_pipe(line))
		return (1);
	i = 0;
	in_quotes = 0;
	quote_char = 0;
	while (line[i])
	{
		handle_quotes(line[i], &in_quotes, &quote_char);
		if (!in_quotes)
		{
			if (check_pipe_errors(line, i))
				return (1);
			if (check_redirect_errors(line, &i))
				return (1);
		}
		i++;
	}
	return (0);
}

static void	add_cmd_to_list(t_cmd **cmd_list, t_cmd **last, t_cmd *cmd)
{
	if (!*cmd_list)
		*cmd_list = cmd;
	else
		(*last)->next = cmd;
	*last = cmd;
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
		add_cmd_to_list(&cmd_list, &last, cmd);
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
			g_signal_received = exec_cmd(cmd_list, env);
		else
			g_signal_received = exec_pipeline(cmd_list, env);
	}
	else
	{
		g_signal_received = 1;
	}
	free_cmd_list(cmd_list);
	free_split(segments);
}
