/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:07:39 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/05 18:14:16 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

#include <stdlib.h>

static int	get_total_len(char **env)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			len++;
			j++;
		}
		i++;
	}
	return (len);
}

char	*copy_env(char **env)
{
	int		i;
	int		j;
	int		k;
	char	*result;

	result = malloc(sizeof(char) * (get_total_len(env) + 1));
	if (!result)
		return (NULL);
	i = 0;
	k = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
		{
			result[k++] = env[i][j++];
		}
		i++;
	}
	result[k] = '\0';
	return (result);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*data;
	char	*line;
	(void)argc;
	(void)argv;

	data = malloc(sizeof(t_shell));
	data->env.str = copy_env(env);
	while ("Minishell gooning")
	{
		line = readline("minishell> ");
		if (!line) //CTRL+D Renvoie NULL
			break ;
		add_history(line);
		if (strncmp(line, "env", 3) == 0)
			printf("%s\n", data->env.str);
		free(line);
	}
	return (0);
}

