# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tobesnar <tobesnar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 16:24:53 by tobesnar          #+#    #+#              #
#    Updated: 2025/05/06 16:57:39 by tobesnar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = minishell
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -Iinclude
LDFLAGS     = -lreadline

SRC         = \
	src/main.c \
	src/utils/env_utils.c \

OBJ         = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@printf "🔧 Compilation en cours"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)
	@printf "\rMinishell compilé ✅   \n"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
