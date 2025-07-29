/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 10:28:10 by tobesnar          #+#    #+#             */
/*   Updated: 2025/07/29 10:28:10 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Lors de l'appel, i = 0, j = 2 et newline = 1.
int	ft_echo(char **argv, int i, int j, int newline)
{
	while (argv[i] && !ft_strncmp(argv[i], "-n", 2))
	{
		while (argv[i][j] == 'n')
			j++;
		if (argv[i][j] != '\0')
			break ;
		newline = 0;
		i++;
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
