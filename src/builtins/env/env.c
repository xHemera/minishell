/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:17:32 by tlize             #+#    #+#             */
/*   Updated: 2025/06/26 14:24:53 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *envp)
{
	while (envp)
	{
		if (envp->value)
			ft_printf("%s=%s\n", envp->key, envp->value);
		else
			ft_printf("%s=\n", envp->key);
		envp = envp->next;
	}
	return (1);
}
