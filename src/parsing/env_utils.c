/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:07:32 by hemera            #+#    #+#             */
/*   Updated: 2025/06/01 13:08:03 by hemera           ###   ########.fr       */
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

char	**env_to_array(t_env *env)
{
	int		size = env_size(env);
	char	**envp = malloc(sizeof(char *) * (size + 1));
	char	*joined;
	int		i = 0;

	if (!envp)
		return (NULL);
	while (env)
	{
		if (env->key && env->value)
		{
			joined = ft_strjoin(env->key, "=");
			if (!joined)
				return (free_split(envp), NULL);
			envp[i] = ft_strjoin(joined, env->value);
			free(joined);
			if (!envp[i])
				return (free_split(envp), NULL);
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
