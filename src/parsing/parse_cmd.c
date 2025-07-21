#include "minishell.h"



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
		expanded_token = ft_expand_variables_quotes(tokens[i], env,
			g_signal_received);
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
