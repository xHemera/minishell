/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:07:39 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/12 13:17:22 by tlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	*data;
	char	*line;
	(void)argc;
	(void)argv;

	data = malloc(sizeof(t_shell));
	data->env.str = copy_env(env);
	while ("Minishell ethical gooning")
	{
		line = readline("minishell> ");
		if (!line) //CTRL+D Renvoie NULL
			break ;
		add_history(line);
		if (strncmp(line, "env", 3) == 0)
			print_env(data);
		free(line);
	}
	free(data);
	return (0);
}

