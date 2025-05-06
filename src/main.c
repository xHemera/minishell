/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:07:39 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/06 16:57:09 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		len++;
		i++;
	}
	return (len);
}

char	*copy_env(char **env)
{
	int		i, j, k;
	char	*result;

	result = malloc(sizeof(char) * (get_total_len(env) + 1));
	i = 0;
	k = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j])
			result[k++] = env[i][j++];
		result[k++] = '\n';
		i++;
	}
	result[k] = '\0';
	return (result);
}

void	print_env(t_shell *data)
{
	write(1, data->env.str, strlen(data->env.str));
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
			print_env(data);
		free(line);
	}
	free(data);
	return (0);
}

