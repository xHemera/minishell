/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:07:39 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/09 15:51:36 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	*data;
	char	*line;
	t_token	token;
	int		j;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_shell));
	if (!data)
		return (1);
	data->env.str = copy_env(env);
	while ("Minishell gooning")
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		add_history(line);
		if (strncmp(line, "env", 3) == 0 && (line[3] == '\0' || line[3] == ' '))
			print_env(data);
		else
		{
			token = tokenize_line(line);
			ft_printf("Nombre de mots : %d\n", token.count);
			j = -1;
			while (++j < token.count)
				ft_printf("Mot %d : %s\n", j + 1, token.words[j]);
			j = -1;
			while (++j < token.count)
				free(token.words[j]);
			free(token.words);
		}
		free(line);
	}
	return (0);
}
