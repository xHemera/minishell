/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:07:39 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/12 17:49:14 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	print_token(t_token *token)
{
	t_token	*tmp;
	int		i;

	tmp = token;
	while (tmp)
	{
		i = 0;
		printf("Words count: %d\n", tmp->count);

		while (i < tmp->count && tmp->words)
		{
			printf("  Word[%d]: %s\n", i, tmp->words[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*data;
	char	*line;
	t_token	token;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_shell));
	data->env.str = copy_env(env);
	while ("Minishell ethical gooning")
	{
		line = readline("minishell> ");
		token = tokenize_line(line);
		if (!line) //CTRL+D Renvoie NULL
			break ;
		add_history(line);
		if (strncmp(line, "env", 3) == 0)
			print_env(data);
		else
			print_token(&token);
		free(line);
	}
	free(data);
	return (0);
}
