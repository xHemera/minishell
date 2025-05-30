NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude
LIBFT = -Linclude/libft -lft -lreadline

SRC_DIR = src
OBJ_DIR = obj

SRCS = main.c \
	$(SRC_DIR)/parsing/env.c \
	$(SRC_DIR)/parsing/split_pipe_aware.c \
	$(SRC_DIR)/parsing/parse_cmd.c \
	$(SRC_DIR)/parsing/redirection_handler.c \
	$(SRC_DIR)/parsing/cmd_utils.c \
	$(SRC_DIR)/parsing/tokenize.c \
	$(SRC_DIR)/parsing/tokenize_utils.c \
	$(SRC_DIR)/exec/exec_builtins.c \
	$(SRC_DIR)/builtins/cd/cd.c \
	$(SRC_DIR)/builtins/pwd/pwd.c \
	$(SRC_DIR)/builtins/exit/exit.c \
	$(SRC_DIR)/builtins/echo/echo.c \
	$(SRC_DIR)/utils/free_utils.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
