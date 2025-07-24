/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:42:28 by marvin            #+#    #+#             */
/*   Updated: 2025/07/24 21:42:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static t_env	*do_unset(t_env *envp)
{
	t_env	*tmp;

	tmp = envp->next;
	if (envp->prev)
		envp->prev->next = envp->next;
	if (envp->next)
		envp->next->prev = envp->prev;
	free(envp->key);
	free(envp->value);
	free(envp);
	return (tmp);
}

int	ft_unset(t_cmd *cmd, t_env *envp)
{
	int		cmd_arg;
	size_t	size;
	t_env	*tmp;

	if (!cmd->args[1])
		return (0);
	while (envp)
	{
		cmd_arg = 1;
		while (cmd->args[cmd_arg])
		{
			size = ft_strlen(cmd->args[cmd_arg]);
			if (ft_strncmp(cmd->args[cmd_arg], envp->key, size) == 0
				&& ft_strlen(envp->key) == size)
			{
				tmp = do_unset(envp);
				envp = tmp;
				break ;
			}
			cmd_arg++;
		}
		if (cmd->args[cmd_arg] == NULL)
			envp = envp->next;
	}
	return (0);
}
