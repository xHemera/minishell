/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:46:32 by marvin            #+#    #+#             */
/*   Updated: 2025/07/24 21:46:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_redirect_error_token(char c)
{
	if (!c)
		ft_putstr_fd("minishell: syntax error near unexpected "
			"token `newline'\n", 2);
	else if (c == '>')
		ft_putstr_fd("minishell: syntax error near unexpected "
			"token `>'\n", 2);
	else if (c == '<')
		ft_putstr_fd("minishell: syntax error near unexpected "
			"token `<'\n", 2);
	else if (c == '|')
		ft_putstr_fd("minishell: syntax error near unexpected "
			"token `|'\n", 2);
}

static int	handle_double_redirect(char *line, int *i, int *j)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
		*j = *i + 2;
	else if (line[*i] == '<' && line[*i + 1] == '<')
		*j = *i + 2;
	else if (line[*i + 1] == '>')
	{
		ft_putstr_fd("minishell: syntax error near unexpected ", 2);
		ft_putstr_fd("token `>'\n", 2);
		return (1);
	}
	else
		*j = *i + 1;
	return (0);
}

int	check_redirect_errors(char *line, int *i)
{
	int	j;

	if (line[*i] == '>' || line[*i] == '<')
	{
		j = *i;
		if (handle_double_redirect(line, i, &j))
			return (1);
		while (line[j] && (line[j] == ' ' || line[j] == '\t'))
			j++;
		if (!line[j] || line[j] == '|' || line[j] == '>' || line[j] == '<')
		{
			print_redirect_error_token(line[j]);
			return (1);
		}
		*i = j - 1;
	}
	return (0);
}

int	check_initial_pipe(char *line)
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

void	handle_quotes(char c, int *in_quotes, char *quote_char)
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
