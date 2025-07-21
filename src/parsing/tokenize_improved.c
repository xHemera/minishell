#include "minishell.h"

static int	is_token_separator(char c)
{
	return (c == ' ' || c == '\t' || c == '<' || c == '>' || c == '|');
}

static int	count_tokens_improved(const char *str)
{
	int	i;
	int	count;
	int	in_token;

	i = 0;
	count = 0;
	in_token = 0;
	while (str[i])
	{
		if (is_token_separator(str[i]) && str[i] != '\'' && str[i] != '"')
		{
			if (in_token)
			{
				count++;
				in_token = 0;
			}
			if (str[i] == '<' || str[i] == '>' || str[i] == '|')
			{
				count++;
				if (str[i + 1] && ((str[i] == '<' && str[i + 1] == '<')
						|| (str[i] == '>' && str[i + 1] == '>')))
					i++;
			}
		}
		else if (!is_token_separator(str[i]) || str[i] == '\'' || str[i] == '"')
		{
			if (!in_token)
				in_token = 1;
		}
		if (str[i] == '\'' || str[i] == '"')
		{
			char	quote;

			quote = str[i];
			i++;
			while (str[i] && str[i] != quote)
				i++;
		}
		i++;
	}
	if (in_token)
		count++;
	return (count);
}

static void	skip_quoted_section(const char *str, int *i)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	if (str[*i])
		(*i)++;
}

static int	find_token_end(const char *str, int start)
{
	int	i;

	i = start;
	while (str[i] && !is_token_separator(str[i]))
	{
		if (str[i] == '\'' || str[i] == '"')
			skip_quoted_section(str, &i);
		else
			i++;
	}
	return (i);
}

static char	*extract_full_token(const char *str, int start, int *end)
{
	char	*result;
	int		len;

	*end = find_token_end(str, start);
	len = *end - start;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	ft_memcpy(result, str + start, len);
	result[len] = '\0';
	return (result);
}

static char	*create_operator_token(char first, char second)
{
	char	*token;

	if (second && ((first == '<' && second == '<')
			|| (first == '>' && second == '>')))
	{
		token = malloc(3);
		if (!token)
			return (NULL);
		token[0] = first;
		token[1] = second;
		token[2] = '\0';
	}
	else
	{
		token = malloc(2);
		if (!token)
			return (NULL);
		token[0] = first;
		token[1] = '\0';
	}
	return (token);
}

static int	handle_operator_token(const char *str, char **tokens,
	int *i, int token_idx)
{
	tokens[token_idx] = create_operator_token(str[*i], str[*i + 1]);
	if (!tokens[token_idx])
		return (0);
	if ((str[*i] == '<' && str[*i + 1] == '<')
		|| (str[*i] == '>' && str[*i + 1] == '>'))
		*i += 2;
	else
		(*i)++;
	return (1);
}

char	**tokenize_improved(const char *str)
{
	char	**tokens;
	int		count;
	int		i;
	int		token_idx;
	int		end;

	count = count_tokens_improved(str);
	tokens = malloc(sizeof(char *) * (count + 1));
	if (!tokens)
		return (NULL);
	i = 0;
	token_idx = 0;
	while (str[i] && token_idx < count)
	{
		i = skip_spaces(str, i);
		if (!str[i])
			break ;
		if (str[i] == '<' || str[i] == '>' || str[i] == '|')
		{
			if (!handle_operator_token(str, tokens, &i, token_idx))
				return (NULL);
		}
		else
		{
			tokens[token_idx] = extract_full_token(str, i, &end);
			if (!tokens[token_idx])
				return (NULL);
			i = end;
		}
		token_idx++;
	}
	tokens[token_idx] = NULL;
	return (tokens);
}
