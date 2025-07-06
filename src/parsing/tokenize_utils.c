#include "minishell.h"

int	skip_spaces(const char *str, int i)
{
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	return (i);
}

int	extract_quoted_token(const char *str, int start, char quote)
{
	int	i;

	i = start + 1;
	while (str[i] && str[i] != quote)
		i++;
	return (i);
}

int	extract_token(const char *str, int start)
{
	int	i;

	i = start;
	while (str[i] && str[i] != ' ' && str[i] != '\t'
		&& str[i] != '\'' && str[i] != '"')
		i++;
	return (i);
}

int	count_tokens(const char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		i = skip_spaces(str, i);
		if (!str[i])
			break ;
		count++;
		if (str[i] == '\'' || str[i] == '"')
			i = extract_quoted_token(str, i, str[i]);
		else
			i = extract_token(str, i);
		if (str[i])
			i++;
	}
	return (count);
}

char	*copy_token(const char *str, int start, int end)
{
	char	*token;
	int		len;

	len = end - start;
	if (len < 0)
		len = 0;
	token = malloc(len + 1);
	if (!token)
		return (NULL);
	if (len > 0)
		ft_memcpy(token, str + start, len);
	token[len] = '\0';
	return (token);
}
