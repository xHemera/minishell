/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:55:31 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/27 18:55:33 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*get_env_value(t_env *env, char *key)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static int	set_env_value(t_env *env, char *key, char *new_value)
{
	while (env)
	{
		if (ft_strncmp(env->key, key, ft_strlen(key) + 1) == 0)
		{
			free(env->value);
			env->value = ft_strdup(new_value);
			return (env->value ? 0 : 1);
		}
		env = env->next;
	}
	return (1);
}

int	ft_cd(char **args, t_env *env)
{
	char	*target_dir;
	char	*home_dir;
	char	old_pwd[1024];
	char	new_pwd[1024];

	if (!args[1])
	{
		home_dir = get_env_value(env, "HOME");
		if (!home_dir)
			return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
		target_dir = home_dir;
	}
	else if (ft_strncmp(args[1], "-", 2) == 0)
	{
		target_dir = get_env_value(env, "OLDPWD");
		if (!target_dir)
			return (ft_putstr_fd("cd: OLDPWD not set\n", 2), 1);
		ft_putstr_fd(target_dir, 1);
		ft_putchar_fd('\n', 1);
	}
	else
		target_dir = args[1];
	if (!getcwd(old_pwd, sizeof(old_pwd)))
		return (perror("cd: getcwd"), 1);
	if (chdir(target_dir) != 0)
		return (perror("cd"), 1);
	if (!getcwd(new_pwd, sizeof(new_pwd)))
		return (perror("cd: getcwd"), 1);
	set_env_value(env, "OLDPWD", old_pwd);
	set_env_value(env, "PWD", new_pwd);
	return (0);
}
