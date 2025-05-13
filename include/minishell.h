/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:55:46 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/13 18:22:55 by tlize            ###   ########.fr       */
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
# define TITLE "[J'adore me Dracaufeu le tortipousse] "

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
	bool			is_builtin;
	char			**args;
	int				arg_count;
	struct s_cmd	*next;
}	t_cmd;

// ##################### //
//       Fonctions       //
// ##################### //

// prompt.c
char	*get_prompt(void);

// env.c
t_env	*env_init(char **envp);

// env_utils.c
t_env	*env_new(char *key, char *value);
void	env_add_back(t_env **head, t_env *new);
void	env_clear(t_env **env);
void	print_env(t_env *env);

// tokenizer.c
t_token	*tokenize_input(char *input);

// builtin_handler.c
int		handle_builtin(char *line, t_env *env);

// cmd_parser.c
t_cmd	*parse_cmd(t_token *tokens);
void	free_tokens(t_token *tokens);

// parser.c
t_cmd	*parse_line(char *line);
void	token_list_clear(t_token **tokens);
void	cmd_list_clear(t_cmd **cmd_list);

// debug.c
void	print_cmd(t_cmd *cmd);

#endif
