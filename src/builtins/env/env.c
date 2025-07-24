/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 21:42:16 by marvin            #+#    #+#             */
/*   Updated: 2025/07/24 21:42:16 by marvin           ###   ########.fr       */
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
