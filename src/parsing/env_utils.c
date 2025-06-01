/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:07:32 by hemera            #+#    #+#             */
/*   Updated: 2025/06/01 14:07:05 by hemera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_size(t_env *env)
{
	int	count = 0;

	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}

static char	*join_key_value(t_env *env)
{
	char	*tmp;
	char	*res;

	tmp = ft_strjoin(env->key, "=");
	if (!tmp)
		return (NULL);
	res = ft_strjoin(tmp, env->value);
	free(tmp);
	return (res);
}

char	**env_to_array(t_env *env)
{
	char	**envp;
	int		i;

	envp = malloc(sizeof(char *) * (env_size(env) + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->key && env->value)
		{
			envp[i] = join_key_value(env);
			if (!envp[i])
				while (i > 0)
					free(envp[--i]), free(envp);
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
