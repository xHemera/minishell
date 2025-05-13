/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:58:47 by tlize             #+#    #+#             */
/*   Updated: 2025/05/13 16:47:53 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Toujours mettre i et newline a 1 , j a 2
int	ft_echo(char **args, int i, int j, int newline)
{
	while (args[i] && !ft_strncmp(args[i], "-n", 2))
	{
		while (args[i][j] == 'n')
			j ++;
		if (args[i][j] != '\0')
			break ;
		newline = 0;
		i ++;
	}
	while (args[i])
	{
		write(1, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}