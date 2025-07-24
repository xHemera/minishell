#include "minishell.h"

int	is_redirect(const char *token)
{
	if (!token)
		return (0);
	if (!ft_strncmp(token, "<", 2) || !ft_strncmp(token, ">", 2)
		|| !ft_strncmp(token, ">>", 3) || !ft_strncmp(token, "<<", 3))
		return (1);
	return (0);
}

static int	handle_first_arg(t_cmd *cmd, char *clean_token)
{
	cmd->name = ft_strdup(clean_token);
	if (!cmd->name)
		return (0);
	if (!cmd_add_arg(cmd, ft_strdup(clean_token)))
	{
		free(cmd->name);
		cmd->name = NULL;
		return (0);
	}
	return (1);
}

static int	handle_additional_arg(t_cmd *cmd, char *clean_token)
{
	return (cmd_add_arg(cmd, ft_strdup(clean_token)));
}

int	add_arg_or_name(t_cmd *cmd, char *token)
{
	char	*clean_token;
	int		result;

	clean_token = remove_quotes(token);
	if (!clean_token)
		return (0);
	if (!cmd->name)
		result = handle_first_arg(cmd, clean_token);
	else
		result = handle_additional_arg(cmd, clean_token);
	free(clean_token);
	return (result);
}
