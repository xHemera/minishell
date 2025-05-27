/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 16:59:11 by tlize             #+#    #+#             */
/*   Updated: 2025/05/27 18:57:40 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//suicide garantit avant la fin de la fonction

int export_add(char **cmd, t_env *envp)
{
    t_env   *new;
    char    **supersplit;
    int     i;

    while (cmd[i])
    {
        supersplit = ft_split(cmd[i], '=');
        new = env_new(supersplit[0], supersplit[1]);
		env_add_back(envp, new);
    }
    return (1);
}

int ft_export(t_cmd *cmd, t_env *envp, int argc)
{
    t_env *test1;
    
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
        return (1);
    }
    else
    {
        while (envp->next)
        {
            envp = envp->next;
        }
        return (export_add(cmd->args, envp));
    }
    return (0);
}
