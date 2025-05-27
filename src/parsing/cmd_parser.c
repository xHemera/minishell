/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:55:30 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/22 17:44:24 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	count_args(t_token *tokens)
{
	int	count;

	count = 0;
	while (tokens)
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

static void	free_args_on_error(char **args, int i)
{
	while (i--)
		free(args[i]);
	free(args);
}

static char	**token_list_to_args(t_token *tokens, int num_args)
{
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * (num_args + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (tokens)
	{
		args[i] = ft_strdup(tokens->value);
		if (!args[i])
		{
			free_args_on_error(args, i);
			return (NULL);
		}
		tokens = tokens->next;
		i++;
	}
	args[i] = NULL;
	return (args);
}

void	free_tokens(t_token *tokens)
{
	t_token	*tmp;

	while (tokens)
	{
		tmp = tokens;
		tokens = tokens->next;
		free(tmp->value);
		free(tmp);
	}
}

t_cmd	*parse_cmd(t_token *tokens)
{
	t_cmd	*cmd;
	int		arg_count;

	cmd = init_cmd();
	if (!cmd)
		return (NULL);
	if (!tokens)
	{
		free(cmd);
		return (NULL);
	}
	cmd->name = ft_strdup(tokens->value);
	if (!cmd->name)
	{
		free(cmd);
		return (NULL);
	}
	arg_count = count_args(tokens);
	cmd->args = token_list_to_args(tokens, arg_count);
	if (!cmd->args)
	{
		free(cmd->name);
		free(cmd);
		return (NULL);
	}
	cmd->is_builtin = ft_strncmp(cmd->name, "env", 4) == 0
		|| ft_strncmp(cmd->name, "export", 7) == 0
		|| ft_strncmp(cmd->name, "unset", 6) == 0;
	free_tokens(tokens);
	return (cmd);
}
