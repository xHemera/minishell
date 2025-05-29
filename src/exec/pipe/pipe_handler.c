/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:23:36 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/22 18:25:18 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

bool	init_pipes(int ***pipes, int nb_pipes)
{
	int	i;

	*pipes = malloc(sizeof(int *) * nb_pipes);
	if (!*pipes)
		return (false);
	i = 0;
	while (i < nb_pipes)
	{
		(*pipes)[i] = malloc(sizeof(int) * 2);
		if (!(*pipes)[i] || !open_pipe((*pipes)[i]))
			return (false);
		i++;
	}
	return (true);
}

void	close_all_pipes(int **pipes, int nb_pipes)
{
	int	i;

	i = 0;
	while (i < nb_pipes)
	{
		close_pipe(pipes[i]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}
