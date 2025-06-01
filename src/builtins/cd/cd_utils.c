/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:54:56 by hemera            #+#    #+#             */
/*   Updated: 2025/06/01 15:00:10 by hemera           ###   ########.fr       */
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
