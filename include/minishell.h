/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:55:46 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/13 11:57:13 by tobesnar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/wait.h>
# include "libft/include/libft.h"

# define RESET   "\033[0m"
# define GREEN   "\033[32m"
# define CYAN	"\033[36m"
# define YELLOW  "\033[33m"

typedef struct s_env
{
	char			*str;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct s_token
{
	int				type;
	char			**words;
	int				count;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_shell
{
	t_env	env;
}			t_shell;

typedef struct s_cmd
{
	char	**argv;
	char	*path;
	int		is_builtin;
}			t_cmd;

// ##################### //
//       Fonctions       //
// ##################### //

// env_utils.c
int		get_total_len(char **env);
char	*copy_env(char **env);
void	print_env(t_shell *data);

// tokenize.c
t_token	tokenize_line(char *input);

// free_cmd.c
void	free_cmd(t_cmd *cmd);

// get_command.c
t_cmd	get_command(t_token token, char **envp);

// prompt.c
char	*get_prompt(void);

#endif
