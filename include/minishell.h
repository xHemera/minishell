/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlize <tlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:12:47 by tobesnar          #+#    #+#             */
/*   Updated: 2025/05/12 15:15:36 by tlize            ###   ########.fr       */
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
	char 	**argv;
	char 	*path;
	int		is_builtin;
}				t_cmd;

// ##################### //
//       Fonctions       //
// ##################### //

// env_utils.c
int		get_total_len(char **env);
char	*copy_env(char **env);
void	print_env(t_shell *data);

#endif
