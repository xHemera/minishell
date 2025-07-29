/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:28:18 by tobesnar          #+#    #+#             */
/*   Updated: 2025/07/29 10:28:18 by tobesnar         ###   ########.fr       */
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
