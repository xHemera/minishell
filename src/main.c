/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   main.c											  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: tobesnar <tobesnar@student.42.fr>			+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/05/05 16:07:39 by tobesnar		  #+#	#+#			 */
/*   Updated: 2025/05/13 12:00:00 by tobesnar		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_shell(t_shell **data, char **env)
{
	*data = malloc(sizeof(t_shell));
	if (!*data)
		return (1);
	(*data)->env.str = copy_env(env);
	if (!(*data)->env.str)
	{
		free(*data);
		return (1);
	}
	return (0);
}

void	print_debug(t_cmd *cmd)
{
	int	i;

	ft_printf("Command: %s\n", cmd->argv[0]);
	i = 0;
	while (cmd->argv[i])
	{
		ft_printf("Argument %d: %s\n", i + 1, cmd->argv[i]);
		i++;
	}
	if (cmd->path)
		ft_printf("Path: %s\n", cmd->path);
	else
		ft_printf("Path: NULL\n");
	ft_printf("Is Builtin: %d\n", cmd->is_builtin);
}

void	handle_input(char *line, char **env)
{
	t_token	token;
	t_cmd	cmd;

	token = tokenize_line(line);
	if (token.count == 0)
		return ;
	cmd = get_command(token, env);
	print_debug(&cmd);
	ft_free_split(cmd.argv);
	free(cmd.path);
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*data;
	char	*line;
	char	*prompt;

	(void)argc;
	(void)argv;
	if (init_shell(&data, env))
		return (1);
	while (1)
	{
		prompt = get_prompt();
		line = readline(prompt);
		free(prompt);
		if (!line)
			break ;
		add_history(line);
		handle_input(line, env);
		free(line);
	}
	free(data->env.str);
	free(data);
	return (0);
}
