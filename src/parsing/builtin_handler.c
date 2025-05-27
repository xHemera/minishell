/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:09:25 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/13 17:43:33 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	handle_builtin(char *line, t_env *env)
{
	if (ft_strncmp(line, "env", 4) == 0)
	{
		print_env(env);
		return (1);
	}
	else if (ft_strncmp(line, "export", 7) == 0)
		ft_putstr_fd("export not implemented yet\n", 1);
	else if (ft_strncmp(line, "unset", 6) == 0)
		ft_putstr_fd("unset not implemented yet\n", 1);
	else if (ft_strncmp(line, "cd", 3) == 0)
		ft_putstr_fd("cd not implemented yet\n", 1);
	else if (ft_strncmp(line, "pwd", 4) == 0)
		ft_putstr_fd("pwd not implemented yet\n", 1);
	else if (ft_strncmp(line, "exit", 5) == 0)
		ft_putstr_fd("exit not implemented yet\n", 1);
	else
		return (0);
	return (1);
}
