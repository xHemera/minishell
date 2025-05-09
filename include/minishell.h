/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:12:47 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/09 15:52:09 by tobesnar         ###   ########.fr       */
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
# include "libft/include/libft.h"

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

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	int				append;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}				t_cmd;


typedef struct s_shell
{
	t_env	env;
}			t_shell;

// ##################### //
//       Fonctions       //
// ##################### //

// env_utils.c
int		get_total_len(char **env);
char	*copy_env(char **env);
void	print_env(t_shell *data);

// tokenize.c
t_token	tokenize_line(char *input);

// tokenize_utils.c
char	*extract_word(const char *start, int len);
void	advance_to_word_end(const char *input, int *i);
void	process_quoted_word(const char *input, int *i, int *start, int *len);
void	process_normal_word(const char *input, int *i, int *start, int *len);

#endif
