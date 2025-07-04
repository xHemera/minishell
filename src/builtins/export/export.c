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
		if (!ft_strncmp(envp->key, maxisplit[0], ft_strlen(maxisplit[0])))
		{
			if (!ft_strncmp(envp->value, " ", 1))
				envp->value = maxisplit[1];
			return (0);
		}
		envp = envp->next;
	}
	return (1);
}

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

static void	print_export_env(t_env *env)
{
	while (env)
	{
		if (env->value && ft_strncmp(env->value, " ", 1) != 0)
			ft_printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			ft_printf("declare -x %s\n", env->key);
		env = env->next;
	}
}

static int	handle_invalid_identifier(char **cmd, char **supersplit, int i)
{
	write(2, "export: `", 9);
	write(2, cmd[i], ft_strlen(cmd[i]));
	write(2, "': not a valid identifier\n", 26);
	free_split(supersplit);
	return (1);
}

static void	add_new_env_var(char **supersplit, t_env *envp)
{
	t_env	*new;

	if (test_double(supersplit, envp))
	{
		if (supersplit[1])
			new = env_new(supersplit[0], supersplit[1]);
		else
			new = env_new(supersplit[0], " ");
		env_add_back(&envp, new);
	}
}

static int	export_add(char **cmd, t_env *envp)
{
	char	**supersplit;
	int		i;
	int		error;

	i = 1;
	error = 0;
	while (cmd[i])
	{
		supersplit = ft_split(cmd[i], '=');
		if (!is_valid_identifier(supersplit[0]))
		{
			error = handle_invalid_identifier(cmd, supersplit, i);
			i++;
			continue ;
		}
		add_new_env_var(supersplit, envp);
		free_split(supersplit);
		i++;
	}
	return (error);
}

int	ft_export(t_cmd *cmd, t_env *envp, int argc)
{
	if (argc == 1)
	{
		print_export_env(envp);
	}
	else
	{
		while (envp->next)
			envp = envp->next;
		return (export_add(cmd->args, envp));
	}
	return (0);
}
