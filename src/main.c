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

// void	handle_input(char *line, char **env)
// {
// 	t_token	token;
// 	t_cmd	cmd;

// 	token = tokenize_line(line);
// 	if (token.count == 0)
// 		return ;
// 	cmd = get_command(token, env);
// 	print_debug(&cmd);
// 	ft_free_split(cmd.argv);
// 	free(cmd.path);
// }

int	main(int argc, char **argv)
{
	char	*line;
	char	*prompt;

	(void)argc;
	(void)argv;
	while (1)
	{
		prompt = get_prompt();
		line = readline(prompt);
		free(prompt);
		if (!line)
			break ;
		add_history(line);
		// handle_input(line, env);
		free(line);
	}
	return (0);
}
