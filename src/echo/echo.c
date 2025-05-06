/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:58:47 by tlize             #+#    #+#             */
/*   Updated: 2025/05/06 15:34:13 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//wip tout caca
void    callecho(char *str)
{
    if (ft_strnstr(str, "echo", 5))
    {
        if ()
    }
}

void    echo(char *str, bool newline)
{
    ft_printf(str);
    if (newline)
        ft_putchar_fd("\n", 1);
}