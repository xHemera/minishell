/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 16:12:47 by tobesnar          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/05/06 16:57:03 by tobesnar         ###   ########.fr       */
=======
/*   Updated: 2025/05/05 20:03:22 by hemera           ###   ########.fr       */
>>>>>>> dcd2226f1f15db38c50a248722c5293b93f2a693
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
# include "libft/includes/libft.h"

typedef struct s_env
{
	char			*str;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

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

#endif
