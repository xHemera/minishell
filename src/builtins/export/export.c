/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:59:11 by tlize             #+#    #+#             */
/*   Updated: 2025/05/19 18:44:30 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//suicide garantit avant la fin de la fonction

int ft_export(t_env *envp, int argc)
{
    if (argc == 1)
    {
        while (envp->next)
        {
            ft_printf(envp->key);
            ft_printf("=");
            ft_printf(envp->value);
            ft_printf("\n");
            envp = envp->next;
        }
    }
    return (0);
}
