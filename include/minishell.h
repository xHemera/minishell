/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 21:47:37 by marvin            #+#    #+#             */
/*   Updated: 2025/07/24 21:47:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*                                INCLUDES                                    */
/* ************************************************************************** */

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/include/libft.h"

/* ************************************************************************** */
/*                              STRUCTURES                                   */
/* ************************************************************************** */

typedef struct s_env
{
	struct s_env	*prev;
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token {
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

/* ************************************************************************** */
/*                           GLOBAL VARIABLES                                */
/* ************************************************************************** */

extern volatile sig_atomic_t g_status;

/* ************************************************************************** */
/*                            FUNCTION PROTOTYPES                            */
/* ************************************************************************** */

/* -------------------------------- BUILTINS -------------------------------- */

// cd.c & cd_utils.c
int		ft_cd(char **args, t_env *env);
char	*get_env_value(t_env *env, char *key);
int		set_env_value(t_env *env, char *key, char *new_value);
int		handle_cd_dash(char **target_dir, t_env *env);
int		handle_cd_home(char **target_dir, t_env *env);
int		cd_change_dir(char *target_dir, t_env *env);

// echo.c
int		ft_echo(char **argv, int i, int j, int newline);

// env.c
int		ft_env(t_env *envp);

// exit.c
int		ft_exit(char **args);

// export.c
int		ft_export(t_cmd *cmd, t_env *envp, int argc);

// pwd.c
int		ft_pwd(void);

// unset.c
int		ft_unset(t_cmd *cmd, t_env *envp);

/* --------------------------------- EXEC ---------------------------------- */

// exec_builtins.c
int		exec_builtin(t_cmd *cmd, t_env *envp);
int		is_builtin(char *cmd_name);
int		is_str_builtin(const char *cmd, const char *name, size_t len);

// exec_cmd.c & exec_cmd_process.c
int		exec_external(t_cmd *cmd, t_env *env);
void	execute_command(t_cmd *cmd, char **envp, t_env *env);
int		exec_cmd(t_cmd *cmd, t_env **env);

// exec_child.c & exec_child_utils.c
int		exec_child(t_cmd *cmd, char **envp, t_env *env);
char	*get_path(t_cmd *cmd, t_env *env);
int		redirect_input(t_cmd *cmd);
int 	redirect_heredoc_input(void);
int		redirect_output(t_cmd *cmd);

// exec_pipeline.c & exec_pipeline_process.c
// exec_pipeline_child.c & exec_pipeline_redirect.c
int		exec_pipeline(t_cmd *cmd_list, t_env **env);
int		setup_pipe(int pipe_fd[2]);
void	handle_child_process(t_cmd *cmd, int pipe_fd[2], int in_fd,
			t_env **env);
void	cleanup_pipe_resources(int pipe_fd[2], int in_fd);
int		wait_for_children(int last_pid);
void	launch_child_process(t_cmd *cmd, int pipe_fd[2], int in_fd,
			t_env **env);
void	parent_process_cleanup(t_cmd *cmd, int pipe_fd[2], int *in_fd);
void	setup_child_redirections(t_cmd *cmd, int pipe_fd[2], int in_fd);
void	handle_child_builtin(t_cmd *cmd, char **envp, t_env *env);
void	handle_direct_execution(t_cmd *cmd, char **envp);

// heredoc_utils.c

// minishell_loop.c
void	minishell_loop(t_env **env);

// parse_and_exec.c
void	parse_and_exec(char *line, t_env **env);

/* -------------------------------- PARSING --------------------------------- */

t_cmd	*cmd_new(void);
int	cmd_add_arg(t_cmd *cmd, char *arg);
void	cmd_clear(t_cmd **head);

// parse_cmd_utils.c
int setup_empty_cmd(t_cmd *cmd);
t_cmd	*cmd_new(void);
int		cmd_add_arg(t_cmd *cmd, char *arg);
void	cmd_clear(t_cmd **head);

// cmd_list_utils.c
t_cmd	*build_cmd_list(char **segments, t_env *env);

// syntax_checker.c
int		has_syntax_error(char *line);

// syntax_checker_utils.c
int		check_redirect_errors(char *line, int *i);
int		check_initial_pipe(char *line);
void	handle_quotes(char c, int *in_quotes, char *quote_char);

// env.c
t_env	*env_init(char **envp);
t_env	*env_new(char *key, char *value);
void	env_add_back(t_env **head, t_env *new);

// env_utils.c
char	**env_to_array(t_env *env);

/* ----------------------------- EXPANSION ------------------------------ */
char	*ft_expand_variables(char *str, t_env *env, int last_exit_code);
char	*ft_expand_variables_quotes(char *str, t_env *env, int last_exit_code);
char	*ft_get_var_value(char *var_name, t_env *env, int last_exit_code);
char	*ft_extract_var_name(char *str, int start);
int		ft_find_var_end(char *str, int start);
char	*ft_replace_variable(char *str, int start, int end, char *value);
int		ft_is_valid_var_char(char c, int first);

// parse_cmd.c
t_cmd	*parse_segment(char *segment);
t_cmd	*parse_segment_with_env(char *segment, t_env *env);
int		handle_token(t_cmd *cmd, char *token, int is_first, t_env *env);

// parse_helpers.c
int		is_redirect(const char *token);
int		add_arg_or_name(t_cmd *cmd, char *token);

// quote_handler.c
int		has_unclosed_quotes(const char *str);
char	*remove_quotes(char *str);
int		should_expand_in_quotes(char quote_type);

/* ---------------------------- REDIRECTION ---------------------------- */
int		handle_redirect(t_cmd *cmd, char **tokens, int *i);
int		handle_input_redirect(t_cmd *cmd, char *token, char *next);
int		handle_output_redirect(t_cmd *cmd, char *token, char *next);
int		set_input_file(t_cmd *cmd, char *file);
int		set_output_file(t_cmd *cmd, char *file, int append);
int		set_heredoc(t_cmd *cmd, char *delimiter);
int		test_file_access(char *file, int flags);

// split_pipe_aware.c
char	**split_pipe_aware(const char *str);

// tokenize_improved.c
char	**tokenize_improved(const char *str);

// tokenize_improved_utils.c
char	*extract_full_token(const char *str, int start, int *end);

// tokenize_utils.c
int		skip_spaces(const char *str, int i);
int		extract_quoted_token(const char *str, int start, char quote);
int		extract_token(const char *str, int start);
int		count_tokens(const char *str);
char	*copy_token(const char *str, int start, int end);

//heredoc
void free_heredoc_file(t_cmd *cmd);
int handle_heredoc(t_cmd *cmd);

/* ----------------------------- TOKENIZE ------------------------------ */
int		is_token_separator(char c);
void	handle_quote_section(const char *str, int *i, char quote);
void	handle_token_separator(const char *str, int *i, int *count,
			int *in_token);
int		count_tokens_improved(const char *str);
int		handle_operator_token(const char *str, char **tokens, int *i,
			int token_idx);

/* -------------------------------- SIGNALS --------------------------------- */

// signals.c
void	handle_sigint(int sig);
void	handle_sigquit(int sig);
void	setup_signals(void);
void	setup_signals_child(void);
void	setup_signals_heredoc(void);

/* --------------------------------- UTILS ---------------------------------- */

// cleanup.c
void	set_global_env(t_env *env);
void	set_global_cmd(t_cmd *cmd);
void	cleanup_and_exit(int exit_code) __attribute__((noreturn));

// free_utils.c
void	free_env(t_env **env);
void	free_split(char **split);
void	free_cmd(t_cmd *cmd);
void	free_cmd_list(t_cmd *cmd);
void	free_tokens(char **tokens);

/* -------------------------------- EXPORT ---------------------------------- */
int		is_valid_identifier(char *str);
int		handle_invalid_identifier(char *invalid_arg);
void	update_existing_env_var(t_env *current, char *value);
int		find_and_update_env_var(t_env *envp, char *key, char *value);
void	add_new_env_var(t_env *envp, char *key, char *value);

#endif
