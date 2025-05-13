/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:58:47 by tlize             #+#    #+#             */
/*   Updated: 2025/05/13 18:08:31 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Toujours mettre i et newline a 1 , j a 2
int	ft_echo(char **argv, int i, int j, int newline)
{
	while (argv[i] && !ft_strncmp(argv[i], "-n", 2))
	{
		while (argv[i][j] == 'n')
			j ++;
		if (argv[i][j] != '\0')
			break ;
		newline = 0;
		i ++;
	}
	while (argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}