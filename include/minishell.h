/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hemera <hemera@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 11:55:46 by tobesnar          #+#    #+#             */
/*   Updated: 2025/06/01 15:06:11 by hemera           ###   ########.fr       */
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
# include <signal.h>

// ! ############################################################### //
// !                           Structures                            //
// ! ############################################################### //

typedef struct s_env
{
	struct s_env	*prev;
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	struct s_token	*prev;
	char			*value;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			*name;
	char			**args;
	char			*input_file;
	char			*output_file;
	int				append;
	char			*heredoc;
	bool			is_builtin;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	t_env	*env;
	t_cmd	*cmd;
}	t_shell;

// ! ############################################################### //
// !                            Fonctions                            //
// ! ############################################################### //

// ! ##################### BUILTINS ##################### //
// buitlins.c
int		ft_cd(char **args, t_env *env);
char	*get_env_value(t_env *env, char *key);
int		set_env_value(t_env *env, char *key, char *new_value);
int		handle_cd_dash(char **target_dir, t_env *env);
int		handle_cd_home(char **target_dir, t_env *env);
int		cd_change_dir(char *target_dir, t_env *env);

int		ft_pwd(void);
// ? int ft_export(t_cmd *cmd, t_env *envp, int argc);
int		ft_echo(char **argv, int i, int j, int newline);
int		ft_exit(char **args);

// ! ##################### EXEC ##################### //
// exec_builtins.c
int		exec_builtin(t_cmd *cmd, t_env *envp);
int		is_builtin(char *cmd_name);
int		is_str_builtin(const char *cmd, const char *name, size_t len);

// exec_cmd.c
int		exec_external(t_cmd *cmd, t_env *env);
int		is_state_changing_builtin(char *cmd_name);
int		exec_cmd(t_cmd *cmd, t_env **env);

// exec_pipeline_utils.c
void	parent_process_cleanup(t_cmd *cmd, int pipe_fd[2], int *in_fd);
void	launch_child_process(t_cmd *cmd, int pipe_fd[2],
			int in_fd, t_env **env);

// exec_pipeline.c
int		exec_pipeline(t_cmd *cmd_list, t_env **env);

// minishell_loop.c
void	minishell_loop(t_env **env);

// parse_and_exec.c
void	parse_and_exec(char *line, t_env **env);

// ! ##################### PARSING ##################### //
// cmd_utils.c
t_cmd	*cmd_new(void);
int		cmd_add_arg(t_cmd *cmd, char *arg);
void	cmd_clear(t_cmd **head);

// env_utils.c
char	**env_to_array(t_env *env);

// env.c
t_env	*env_init(char **envp);
t_env	*env_new(char *key, char *value);
void	env_add_back(t_env **head, t_env *new);

// parse_cmd.c
t_cmd	*parse_segment(char *segment);

// redirection_handler.c
int		handle_redirect(t_cmd *cmd, char **tokens, int *i);

// split_pipe_aware.c
char	**split_pipe_aware(const char *str);

// tokenize_utils.c
int		skip_spaces(const char *str, int i);
int		extract_quoted_token(const char *str, int start, char quote);
int		extract_token(const char *str, int start);
int		count_tokens(const char *str);
char	*copy_token(const char *str, int start, int end);

// tokenize.c
char	**tokenize_simple(const char *str);

// ! ##################### UTILS ##################### //
// free_utils.c
void	free_env(t_env **env);
void	free_split(char **split);
void	free_cmd(t_cmd *cmd);
void	free_cmd_list(t_cmd *cmd);
void	free_tokens(char **tokens);

#endif
