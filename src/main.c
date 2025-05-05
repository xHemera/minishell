/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:07:39 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/05 17:01:54 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	prompt_loop(char **env)
{
	char	*line;

	while ("The prophecy is true")
	{
		line = readline("minishell> ");
		if (!line) //CTRL+D Renvoie NULL
			break ;
		if (*line)
			add_history(line);
		//TODO
		free(line);
	}
}

int	main(void)
{

	return (0);
}
