/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:37:17 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/09 15:52:06 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// void	init_cmd(t_cmd *cmd)
// {
// 	cmd->args = NULL;
// 	cmd->infile = NULL;
// 	cmd->outfile = NULL;
// 	cmd->append = 0;
// 	cmd->next = NULL;
// }

// int	is_redirect(char *token)
// {
// 	if (!token)
// 		return (0);
// 	return (!ft_strcmp(token, ">") || !ft_strcmp(token, ">>")
// 		|| !ft_strcmp(token, "<"));
// }

// int	is_pipe(char *token)
// {
// 	if (!token)
// 		return (0);
// 	return (!ft_strcmp(token, "|"));
// }

// void	add_arg(t_cmd *cmd, char *token)
// {
// 	int		len;
// 	char	**new_args;

// 	len = 0;
// 	while (cmd->args && cmd->args[len])
// 		len++;
// 	new_args = malloc(sizeof(char *) * (len + 2));
// 	if (!new_args)
// 		return ;
// 	len = 0;
// 	while (cmd->args && cmd->args[len])
// 	{
// 		new_args[len] = cmd->args[len];
// 		len++;
// 	}
// 	new_args[len++] = ft_strdup(token);
// 	new_args[len] = NULL;
// 	free(cmd->args);
// 	cmd->args = new_args;
// }

