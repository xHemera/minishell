/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:07:32 by hemera            #+#    #+#             */
/*   Updated: 2025/06/01 14:23:38 by hemera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	env_size(t_env *env)
{
	int	count;

	count = 0;
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
	if (env->value)
		res = ft_strjoin(tmp, env->value);
	else
		res = ft_strjoin(tmp, "");
	free(tmp);
	return (res);
}

static void	free_env_array(char **envp, int i)
{
	while (i > 0)
	{
		i--;
		free(envp[i]);
	}
	free(envp);
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
		if (env->key)
		{
			envp[i] = join_key_value(env);
			if (!envp[i])
			{
				free_env_array(envp, i);
				return (NULL);
			}
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
