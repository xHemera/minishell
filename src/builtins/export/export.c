/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:42:23 by marvin            #+#    #+#             */
/*   Updated: 2025/07/24 22:26:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

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

static int	process_export_arg(char *arg, t_env *envp)
{
	char	**split;

	if (!arg || arg[0] == '=')
		return (handle_invalid_identifier(arg));
	split = ft_split(arg, '=');
	if (!split || !split[0] || !is_valid_identifier(split[0]))
	{
		if (split)
			free_split(split);
		return (handle_invalid_identifier(arg));
	}
	if (!find_and_update_env_var(envp, split[0], split[1]))
		add_new_env_var(envp, split[0], split[1]);
	free_split(split);
	return (0);
}

int	ft_export(t_cmd *cmd, t_env *envp, int argc)
{
	int	i;
	int	error;

	if (argc == 1)
	{
		print_export_env(envp);
		return (0);
	}
	i = 1;
	error = 0;
	while (cmd->args[i])
	{
		error |= process_export_arg(cmd->args[i], envp);
		i++;
	}
	return (error);
}
