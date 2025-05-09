/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:37:20 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/09 15:51:59 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	fill_redirs(t_cmd *cmd, char ***tokens)
// {
// 	while (**tokens && is_redirect(**tokens))
// 	{
// 		if (!ft_strcmp(**tokens, ">"))
// 		{
// 			(*tokens)++;
// 			cmd->outfile = ft_strdup(**tokens);
// 		}
// 		else if (!ft_strcmp(**tokens, ">>"))
// 		{
// 			(*tokens)++;
// 			cmd->outfile = ft_strdup(**tokens);
// 			cmd->append = 1;
// 		}
// 		else if (!ft_strcmp(**tokens, "<"))
// 		{
// 			(*tokens)++;
// 			cmd->infile = ft_strdup(**tokens);
// 		}
// 		(*tokens)++;
// 	}
// }

// void	fill_args(t_cmd *cmd, char ***tokens)
// {
// 	while (**tokens && !is_pipe(**tokens) && !is_redirect(**tokens))
// 	{
// 		add_arg(cmd, **tokens);
// 		(*tokens)++;
// 	}
// }

// void	add_cmd(t_cmd **head, t_cmd **current, char ***tokens)
// {
// 	t_cmd	*cmd;

// 	cmd = malloc(sizeof(t_cmd));
// 	if (!cmd)
// 		return ;
// 	init_cmd(cmd);
// 	fill_args(cmd, tokens);
// 	fill_redirs(cmd, tokens);
// 	if (**tokens && is_pipe(**tokens))
// 		(*tokens)++;
// 	if (!*head)
// 		*head = cmd;
// 	else
// 		(*current)->next = cmd;
// 	*current = cmd;
// }

// t_cmd	*parse_tokens(char **tokens)
// {
// 	t_cmd	*head;
// 	t_cmd	*current;
// 	int		i;

// 	head = NULL;
// 	current = NULL;
// 	i = 0;
// 	while (tokens[i])
// 	{
// 		add_cmd(&head, &current, &tokens[i]);
// 	}
// 	return (head);
// }
