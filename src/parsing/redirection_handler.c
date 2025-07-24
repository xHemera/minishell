#include "minishell.h"

int	handle_redirect(t_cmd *cmd, char **tokens, int *i)
{
	char	*token;
	char	*next;
	int		result;

	token = tokens[*i];
	next = tokens[*i + 1];
	if (!next)
		return (0);
	if (token[0] == '<')
		result = handle_input_redirect(cmd, token, next);
	else
		result = handle_output_redirect(cmd, token, next);
	if (result)
		(*i)++;
	return (result);
}
