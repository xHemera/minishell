NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude
LIBFT = -Linclude/libft -lft -lreadline

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(SRC_DIR)/main.c \
	$(SRC_DIR)/echo/echo.c \
	$(SRC_DIR)/utils/env_utils.c \
	$(SRC_DIR)/utils/get_command.c

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
