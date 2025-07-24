NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude
LIBFT = -Linclude/libft -lft -lreadline

SRC_DIR = src
OBJ_DIR = obj

SRCS = main.c \
	$(SRC_DIR)/builtins/cd/cd.c \
	$(SRC_DIR)/builtins/cd/cd_utils.c \
	$(SRC_DIR)/builtins/echo/echo.c \
	$(SRC_DIR)/builtins/env/env.c \
	$(SRC_DIR)/builtins/exit/exit.c \
	$(SRC_DIR)/builtins/export/export.c \
	$(SRC_DIR)/builtins/export/export_utils.c \
	$(SRC_DIR)/builtins/pwd/pwd.c \
	$(SRC_DIR)/builtins/unset/unset.c \
	$(SRC_DIR)/exec/exec_builtins.c \
	$(SRC_DIR)/exec/exec_child.c \
	$(SRC_DIR)/exec/exec_child_utils.c \
	$(SRC_DIR)/exec/exec_path_utils.c \
	$(SRC_DIR)/exec/exec_cmd.c \
	$(SRC_DIR)/exec/exec_cmd_utils.c \
	$(SRC_DIR)/exec/exec_cmd_process.c \
	$(SRC_DIR)/exec/exec_pipeline_utils.c \
	$(SRC_DIR)/exec/exec_pipeline.c \
	$(SRC_DIR)/exec/exec_pipeline_process.c \
	$(SRC_DIR)/exec/exec_pipeline_child.c \
	$(SRC_DIR)/exec/exec_pipeline_redirect.c \
	$(SRC_DIR)/exec/minishell_loop.c \
	$(SRC_DIR)/exec/parse_and_exec.c \
	$(SRC_DIR)/exec/redirect_handler.c \
	$(SRC_DIR)/parsing/cmd_utils.c \
	$(SRC_DIR)/parsing/cmd_list_utils.c \
	$(SRC_DIR)/parsing/env_utils.c \
	$(SRC_DIR)/parsing/env.c \
	$(SRC_DIR)/parsing/expansion.c \
	$(SRC_DIR)/parsing/expansion_utils.c \
	$(SRC_DIR)/parsing/expansion_var_utils.c \
	$(SRC_DIR)/parsing/expansion_quotes.c \
	$(SRC_DIR)/parsing/parse_cmd.c \
	$(SRC_DIR)/parsing/parse_cmd_utils.c \
	$(SRC_DIR)/parsing/parse_segment.c \
	$(SRC_DIR)/parsing/parse_helpers.c \
	$(SRC_DIR)/parsing/quote_handler.c \
	$(SRC_DIR)/parsing/redirection_handler.c \
	$(SRC_DIR)/parsing/redirection_utils.c \
	$(SRC_DIR)/parsing/redirection_file_utils.c \
	$(SRC_DIR)/parsing/split_pipe_aware.c \
	$(SRC_DIR)/parsing/syntax_checker.c \
	$(SRC_DIR)/parsing/syntax_checker_utils.c \
	$(SRC_DIR)/parsing/tokenize_improved.c \
	$(SRC_DIR)/parsing/tokenize_improved_utils.c \
	$(SRC_DIR)/parsing/tokenize_quote_utils.c \
	$(SRC_DIR)/parsing/tokenize_utils.c \
	$(SRC_DIR)/signals/signals.c \
	$(SRC_DIR)/utils/free_utils.c \
	$(SRC_DIR)/utils/cleanup.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
