/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 13:40:02 by hemera            #+#    #+#             */
/*   Updated: 2025/06/01 14:04:57 by hemera           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void minishell_loop(t_env **env)
{
    char *line;

    while (1)
    {
        line = readline("minishell> ");
        if (!line)
            exit(0);
        if (*line)
        {
            add_history(line);
            parse_and_exec(line, env);
        }
        free(line);
    }
}
