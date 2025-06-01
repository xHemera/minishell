/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 15:53:18 by tobesnar          #+#    #+#             */
/*   Updated: 2025/06/01 14:08:26 by hemera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
    t_shell data;

    (void)argc;
    (void)argv;
    data.env = env_init(envp);
    if (!data.env)
    {
        fprintf(stderr, "Error: Failed to initialize environment\n");
        return (1);
    }
    minishell_loop(&data.env);
    free_env(&data.env);
    return (0);
}
