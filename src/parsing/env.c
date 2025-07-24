/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:45:31 by marvin            #+#    #+#             */
/*   Updated: 2025/07/24 21:45:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_new(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
	{
		free(key);
		free(value);
		return (NULL);
	}
	node->key = key;
	node->value = value;
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

void	env_add_back(t_env **head, t_env *new)
{
	t_env	*temp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
	new->prev = temp;
}

static char	*get_key(const char *env)
{
	size_t	len;
	char	*key;

	len = 0;
	while (env[len] && env[len] != '=')
		len++;
	key = malloc(len + 1);
	if (!key)
		return (NULL);
	ft_strlcpy(key, env, len + 1);
	return (key);
}

static char	*get_value(const char *env)
{
	while (*env && *env != '=')
		env++;
	if (!*env || !*(env + 1))
		return (NULL);
	return (ft_strdup(env + 1));
}

t_env	*env_init(char **envp)
{
	t_env	*head;
	t_env	*new;
	char	*empty;

	head = NULL;
	empty = "_";
	while (*envp)
	{
		new = env_new(get_key(*envp), get_value(*envp));
		if (!new)
		{
			free_env(&head);
			return (NULL);
		}
		if (*new->key != *empty)
			env_add_back(&head, new);
		else
		{
			free(new->key);
			free(new->value);
			free(new);
		}
		envp++;
	}
	return (head);
}
