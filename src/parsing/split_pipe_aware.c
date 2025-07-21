#include "minishell.h"

static int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

static void	skip_quoted(const char *str, int *i)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i] == quote)
		(*i)++;
}

static int	count_cmds(const char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (str[i])
	{
		if (is_quote(str[i]))
			skip_quoted(str, &i);
		if (str[i] == '|')
			count++;
		if (str[i])
			i++;
	}
	return (count);
}

static char	*extract_segment(const char *str, int *pos)
{
	int		start;
	int		i;
	char	*substr;
	char	*trimmed;

	while (is_whitespace(str[*pos]))
		(*pos)++;
	start = *pos;
	i = start;
	while (str[i])
	{
		if (is_quote(str[i]))
			skip_quoted(str, &i);
		else if (str[i] == '|')
			break ;
		else
			i++;
	}
	*pos = i + (str[i] == '|');
	substr = ft_substr(str, start, i - start);
	trimmed = ft_strtrim(substr, " \t");
	free(substr);
	return (trimmed);
}

char	**split_pipe_aware(const char *str)
{
	int		cmd_count;
	char	**result;
	int		pos;
	int		i;

	cmd_count = count_cmds(str);
	result = malloc(sizeof(char *) * (cmd_count + 1));
	if (!result)
		return (NULL);
	pos = 0;
	i = 0;
	while (i < cmd_count)
	{
		result[i] = extract_segment(str, &pos);
		if (!result[i])
		{
			while (i-- > 0)
				free(result[i]);
			free(result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}
