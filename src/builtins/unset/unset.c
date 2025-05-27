/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:52:07 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/27 18:55:42 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	remove_env_node(t_env **env, t_env *node_to_remove)
{
	if (node_to_remove->prev)
		node_to_remove->prev->next = node_to_remove->next;
	else
		*env = node_to_remove->next;
	if (node_to_remove->next)
		node_to_remove->next->prev = node_to_remove->prev;
	free(node_to_remove->key);
	free(node_to_remove->value);
	free(node_to_remove);
}

static int	unset_variable(t_env **env, char *var_name)
{
	t_env	*current;

	current = *env;
	while (current)
	{
		if (ft_strncmp(current->key, var_name, ft_strlen(var_name) + 1) == 0)
		{
			remove_env_node(env, current);
			return (0);
		}
		current = current->next;
	}
	return (0);
}

int	ft_unset(char **args, t_env **env)
{
	int	i;
	int	exit_status;

	if (!args[1])
		return (0);
	exit_status = 0;
	i = 1;
	while (args[i])
	{
		if (!is_valid_identifier(args[i]))
		{
			ft_putstr_fd("unset: not a valid identifier: ", 2);
			ft_putstr_fd(args[i], 2);
			ft_putchar_fd('\n', 2);
			exit_status = 1;
		}
		else
			unset_variable(env, args[i]);
		i++;
	}
	return (exit_status);
}
