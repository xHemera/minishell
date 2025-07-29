/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:33:43 by tobesnar          #+#    #+#             */
/*   Updated: 2025/07/29 10:33:43 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	has_syntax_error(char *line)
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
