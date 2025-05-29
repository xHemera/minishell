/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:01:34 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/29 14:37:39 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	env_free(t_env *env)
{
	if (!env)
		return ;
	free(env->key);
	free(env->value);
	free(env);
}

void	env_clear(t_env **env_list)
{
	t_env	*current;
	t_env	*next;

	if (!env_list)
		return ;
	current = *env_list;
	while (current)
	{
		next = current->next;
		env_free(current);
		current = next;
	}
	*env_list = NULL;
}

static char	*get_key(const char *env)
{
	size_t	len;
	size_t	i;
	char	*key;

	len = 0;
	while (env[len] && env[len] != '=')
		len++;
	key = malloc(sizeof(char) * (len + 1));
	if (!key)
		return (NULL);
	i = 0;
	while (i < len)
	{
		key[i] = env[i];
		i++;
	}
	key[len] = '\0';
	return (key);
}

static char	*get_value(const char *env)
{
	size_t	start;
	char	*value;

	start = 0;
	while (env[start] && env[start] != '=')
		start++;
	if (env[start] == '\0')
		return (NULL);
	start++;
	value = strdup(env + start);
	return (value);
}

t_env	*env_init(char **envp)
{
	t_env	*head;
	t_env	*new;

	head = NULL;
	while (*envp)
	{
		new = env_new(get_key(*envp), get_value(*envp));
		if (!new)
		{
			env_clear(&head);
			return (NULL);
		}
		env_add_back(&head, new);
		envp++;
	}
	return (head);
}
