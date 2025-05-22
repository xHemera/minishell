/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:55:46 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/22 18:27:57 by tobesnar         ###   ########.fr       */
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
# define TITLE "[Jarvis, nettoie moi le gland] "

// Structure pour l'environnement
typedef struct s_env
{
	struct s_env	*prev;
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// Structure pour les tokens
typedef struct s_token
{
	char			*value;
	struct s_token	*next;
}	t_token;

// Structure pour les commandes
typedef struct s_cmd
{
	char			*name;
	char			**args;
	char			*input_file;
	char			*output_file;
	int				append;
	char			*heredoc_delimiter;
	bool			is_builtin;
	struct s_cmd	*next;
}	t_cmd;

// ##################### //
//       Fonctions       //
// ##################### //

// prompt.c
char		*get_prompt(void);

// env.c
t_env		*env_init(char **envp);

// env_utils.c
t_env		*env_new(char *key, char *value);
void		env_add_back(t_env **head, t_env *new);
void		env_clear(t_env **env);
void		print_env(t_env *env);

// tokenizer.c
t_token		*tokenize_input(char *input);

// tokenizer_utils.c
int			handle_quotes(char *line, int *i, char quote_char);
char		*process_quoted_content(char *raw_token);
t_token		*create_new_token(char *token_value);
t_token		*add_token_to_list(t_token *head, char *token_value);

// builtin_handler.c
int			handle_builtin(char *line, t_env *env);

// builtins
// int		ft_echo(char **argv, int i, int j, int newline);
// int		ft_export(t_cmd *cmd, t_env *envp);

// cmd_parser.c
t_cmd		*parse_cmd(t_token *tokens);
void		free_tokens(t_token *tokens);

// parser.c
t_cmd		*parse_line(char *line);
void		token_list_clear(t_token **tokens);
void		cmd_list_clear(t_cmd **cmd_list);
t_cmd		*init_cmd(void);

// debug.c
void		print_cmd(t_cmd *cmd);

// pipe_utils.c
bool		open_pipe(int pipefd[2]);
void		close_pipe(int pipefd[2]);

// pipe_handler.c
bool		init_pipes(int ***pipes, int nb_pipes);
void		close_all_pipes(int **pipes, int nb_pipes);

#endif
