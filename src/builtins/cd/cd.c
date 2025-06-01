/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:55:31 by tobesnar          #+#    #+#             */
/*   Updated: 2025/06/01 15:04:05 by hemera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	set_env_value(t_env *env, char *key, char *new_value)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
		{
			free(env->value);
			env->value = ft_strdup(new_value);
			if (env->value)
				return (0);
			return (1);
		}
		env = env->next;
	}
	return (1);
}

int	ft_cd(char **args, t_env *env)
{
	char	*target_dir;

	if (!args[1])
	{
		if (handle_cd_home(&target_dir, env))
			return (1);
	}
	else if (ft_strncmp(args[1], "-", 2) == 0)
	{
		if (handle_cd_dash(&target_dir, env))
			return (1);
	}
	else
		target_dir = args[1];
	return (cd_change_dir(target_dir, env));
}
