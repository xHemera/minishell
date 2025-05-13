/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:07:39 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/13 11:26:00 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_shell	*data;
	char	*line;
	t_token	token;
	t_cmd	cmd;
	int		i;

	(void)argc;
	(void)argv;
	data = malloc(sizeof(t_shell));
	if (!data)
		return (1);
	data->env.str = copy_env(env);
	if (!data->env.str)
	{
		free(data);
		return (1);
	}
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
			break ;
		add_history(line);

		token = tokenize_line(line);
		if (token.count == 0)
		{
			free(line);
			continue ;
		}
		cmd = get_command(token, env);
		ft_printf("Command: %s\n", cmd.argv[0]);
		i = 0;
		while (cmd.argv[i] != NULL)
		{
			ft_printf("Argument %d: %s\n", i + 1, cmd.argv[i]);
			i++;
		}
		ft_printf("Path: %s\n", cmd.path ? cmd.path : "NULL");
		ft_printf("Is Builtin: %d\n", cmd.is_builtin);
		ft_free_split(cmd.argv);
		free(cmd.path);
		free(line);
	}
	free(data->env.str);
	free(data);
	return (0);
}
