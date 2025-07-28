/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:42:03 by marvin            #+#    #+#             */
/*   Updated: 2025/07/24 21:42:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_cd_home(char **target_dir, t_env *env)
{
	char	*home_dir;

	home_dir = get_env_value(env, "HOME");
	if (!home_dir)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	*target_dir = home_dir;
	return (0);
}

int	handle_cd_dash(char **target_dir, t_env *env)
{
	*target_dir = get_env_value(env, "OLDPWD");
	if (!*target_dir)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (1);
	}
	ft_putstr_fd(*target_dir, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}

int	cd_change_dir(char *target_dir, t_env *env)
{
	char	old_pwd[1024];
	char	new_pwd[1024];

	if (!getcwd(old_pwd, sizeof(old_pwd)))
	{
		perror("cd: getcwd");
		return (1);
	}
	if (chdir(target_dir) != 0)
	{
		perror("cd");
		return (1);
	}
	if (!getcwd(new_pwd, sizeof(new_pwd)))
	{
		perror("cd: getcwd");
		return (1);
	}
	set_env_value(env, "OLDPWD", old_pwd);
	set_env_value(env, "PWD", new_pwd);
	return (0);
}
