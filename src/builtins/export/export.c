/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:59:11 by tlize             #+#    #+#             */
/*   Updated: 2025/06/26 14:14:04 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	test_double(char **maxisplit, t_env *envp)
{
	while (envp)
	{
		if (!ft_strncmp(envp->key, maxisplit[0], strlen(maxisplit[0])))
		{
			if (!ft_strncmp(envp->value, " ", 1))
				envp->value = maxisplit[1];
			return (0);
		}
		envp = envp->next;
	}
	return (1);
}

static int	export_add(char **cmd, t_env *envp)
{
	t_env	*new;
	char	**supersplit;
	int		i;

	i = 1;
	while (cmd[i])
	{
		supersplit = ft_split(cmd[i], '=');
		if (test_double(supersplit, envp))
		{
			if (supersplit[1])
				new = env_new(supersplit[0], supersplit[1]);
			else
				new = env_new(supersplit[0], " ");
			env_add_back(&envp, new);
		}
		i++;
	}
	return (1);
}

int	ft_export(t_cmd *cmd, t_env *envp, int argc)
{
	if (argc == 1)
	{
		while (envp)
		{
			ft_printf("%s=%s\n", envp->key, envp->value);
			envp = envp->next;
		}
	}
	else
	{
		while (envp->next)
			envp = envp->next;
		return (export_add(cmd->args, envp));
	}
	return (0);
}
