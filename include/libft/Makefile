# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tlize <tlize@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/05 17:46:40 by tlize             #+#    #+#              #
#    Updated: 2025/05/05 17:46:41 by tlize            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# == Makefile pour libft == 

SRC_DIR = src
GNL_DIR = $(SRC_DIR)/gnl
PRINTF_DIR = $(SRC_DIR)/ft_printf
OBJ_DIR = obj
INC_DIR = includes

# == Fichiers sources ==
SRC_FILES = \
		$(SRC_DIR)/ft_atoi.c \
		$(SRC_DIR)/ft_atol.c \
		$(SRC_DIR)/ft_bzero.c \
		$(SRC_DIR)/ft_calloc.c \
		$(SRC_DIR)/ft_isalnum.c \
		$(SRC_DIR)/ft_isalpha.c \
		$(SRC_DIR)/ft_isascii.c \
		$(SRC_DIR)/ft_isdigit.c \
		$(SRC_DIR)/ft_isprint.c \
		$(SRC_DIR)/ft_itoa.c \
		$(SRC_DIR)/ft_memchr.c \
		$(SRC_DIR)/ft_memcmp.c \
		$(SRC_DIR)/ft_memcpy.c \
		$(SRC_DIR)/ft_memmove.c \
		$(SRC_DIR)/ft_memset.c \
		$(SRC_DIR)/ft_putchar_fd.c \
		$(SRC_DIR)/ft_putendl_fd.c \
		$(SRC_DIR)/ft_putstr_fd.c \
		$(SRC_DIR)/ft_split.c \
		$(SRC_DIR)/ft_strchr.c \
		$(SRC_DIR)/ft_strdup.c \
		$(SRC_DIR)/ft_striteri.c \
		$(SRC_DIR)/ft_strjoin.c \
		$(SRC_DIR)/ft_strlcat.c \
		$(SRC_DIR)/ft_strlcpy.c \
		$(SRC_DIR)/ft_strlen.c \
		$(SRC_DIR)/ft_strmapi.c \
		$(SRC_DIR)/ft_strncmp.c \
		$(SRC_DIR)/ft_strmcpy.c \
		$(SRC_DIR)/ft_strnstr.c \
		$(SRC_DIR)/ft_strrchr.c \
		$(SRC_DIR)/ft_strtrim.c \
		$(SRC_DIR)/ft_substr.c \
		$(SRC_DIR)/ft_tolower.c \
		$(SRC_DIR)/ft_toupper.c

GNL_FILES = \
		$(GNL_DIR)/get_next_line.c\
		$(GNL_DIR)/get_next_line_utils.c

PRINTF_FILES = \
		$(PRINTF_DIR)/ft_printf.c \
		$(PRINTF_DIR)/ft_printfc.c \
		$(PRINTF_DIR)/ft_printfd.c \
		$(PRINTF_DIR)/ft_printfp.c \
		$(PRINTF_DIR)/ft_printfs.c \
		$(PRINTF_DIR)/ft_printfu.c \
		$(PRINTF_DIR)/ft_printfx.c

SRCS = $(SRC_FILES) $(GNL_FILES) $(PRINTF_FILES)

# == Fichiers objets ==
OBJ_FILES = \
		$(OBJ_DIR)/ft_atoi.o \
		$(OBJ_DIR)/ft_atol.o \
		$(OBJ_DIR)/ft_bzero.o \
		$(OBJ_DIR)/ft_calloc.o \
		$(OBJ_DIR)/ft_isalnum.o \
		$(OBJ_DIR)/ft_isalpha.o \
		$(OBJ_DIR)/ft_isascii.o \
		$(OBJ_DIR)/ft_isdigit.o \
		$(OBJ_DIR)/ft_isprint.o \
		$(OBJ_DIR)/ft_itoa.o \
		$(OBJ_DIR)/ft_memchr.o \
		$(OBJ_DIR)/ft_memcmp.o \
		$(OBJ_DIR)/ft_memcpy.o \
		$(OBJ_DIR)/ft_memmove.o \
		$(OBJ_DIR)/ft_memset.o \
		$(OBJ_DIR)/ft_putchar_fd.o \
		$(OBJ_DIR)/ft_putendl_fd.o \
		$(OBJ_DIR)/ft_putnbr_fd.o \
		$(OBJ_DIR)/ft_putstr_fd.o \
		$(OBJ_DIR)/ft_split.o \
		$(OBJ_DIR)/ft_strchr.o \
		$(OBJ_DIR)/ft_strdup.o \
		$(OBJ_DIR)/ft_striteri.o \
		$(OBJ_DIR)/ft_strlcat.o \
		$(OBJ_DIR)/ft_strlcpy.o \
		$(OBJ_DIR)/ft_strlen.o \
		$(OBJ_DIR)/ft_strmapi.o \
		$(OBJ_DIR)/ft_strncmp.o \
		$(OBJ_DIR)/ft_strncpy.o \
		$(OBJ_DIR)/ft_strnstr.o \
		$(OBJ_DIR)/ft_strrchr.o \
		$(OBJ_DIR)/ft_strtrim.o \
		$(OBJ_DIR)/ft_substr.o \
		$(OBJ_DIR)/ft_tolower.o \
		$(OBJ_DIR)/ft_toupper.o \
		$(OBJ_DIR)/gnl_get_next_line.o \
		$(OBJ_DIR)/gnl_get_next_line_utils.o \
		$(OBJ_DIR)/printf_ft_printf.o \
		$(OBJ_DIR)/printf_ft_printfc.o \
		$(OBJ_DIR)/printf_ft_printfd.o \
		$(OBJ_DIR)/printf_ft_printfp.o \
		$(OBJ_DIR)/printf_ft_printfs.o \
		$(OBJ_DIR)/printf_ft_printfu.o \
		$(OBJ_DIR)/printf_ft_printfx.o 

OBJS = $(OBJ_FILES)

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I$(INC_DIR)

# == Couleurs pour les messages dans le terminal ==
YELLOW = \033[1;33m
NC = \033[0m

all:		$(NAME)

$(NAME):	$(OBJS)
			ar rsc $(NAME) $(OBJS)
			@echo "$(YELLOW)libft.a created successfully!$(NC)"

# == Compilation des fichiers .c en .o ==
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/gnl_%.o: $(GNL_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/printf_%.o: $(PRINTF_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# == Nettoyage des fichiers objets ==
clean:
			rm -f $(OBJS)
			@echo "$(YELLOW)Object files cleaned.$(NC)"

fclean:		clean
			rm -f $(NAME)
			@echo "$(YELLOW)Library removed.$(NC)"

# == Recompilation complète ==
re:		fclean all

.PHONY:		all clean fclean re
