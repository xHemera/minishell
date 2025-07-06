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

void	add_arg_or_name(t_cmd *cmd, char *token)
{
	char	*clean_token;

	clean_token = remove_quotes(token);
	if (!clean_token || clean_token[0] == '\0')
	{
		free(clean_token);
		return ;
	}
	if (!cmd->name)
	{
		cmd->name = ft_strdup(clean_token);
		cmd_add_arg(cmd, ft_strdup(clean_token));
	}
	else
	{
		cmd_add_arg(cmd, ft_strdup(clean_token));
	}
	free(clean_token);
}
