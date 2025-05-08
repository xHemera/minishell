NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

# Headers
INCLUDES = -I./include

# Source files
FT_PRINTF_SRCS = \
	./src/ft_printf/ft_printf.c \
	./src/ft_printf/ft_printfc.c \
	./src/ft_printf/ft_printfd.c \
	./src/ft_printf/ft_printfp.c \
	./src/ft_printf/ft_printfs.c \
	./src/ft_printf/ft_printfu.c \
	./src/ft_printf/ft_printfx.c

GNL_SRCS = \
	./src/gnl/get_next_line.c \
	./src/gnl/get_next_line_utils.c

LIBFT_SRCS = \
	./src/libft/ft_atoi.c \
	./src/libft/ft_atol.c \
	./src/libft/ft_bzero.c \
	./src/libft/ft_calloc.c \
	./src/libft/ft_isalnum.c \
	./src/libft/ft_isalpha.c \
	./src/libft/ft_isascii.c \
	./src/libft/ft_isdigit.c \
	./src/libft/ft_isprint.c \
	./src/libft/ft_itoa.c \
	./src/libft/ft_memchr.c \
	./src/libft/ft_memcmp.c \
	./src/libft/ft_memcpy.c \
	./src/libft/ft_memmove.c \
	./src/libft/ft_memset.c \
	./src/libft/ft_putchar_fd.c \
	./src/libft/ft_putendl_fd.c \
	./src/libft/ft_putnbr_fd.c \
	./src/libft/ft_putstr_fd.c \
	./src/libft/ft_split.c \
	./src/libft/ft_strchr.c \
	./src/libft/ft_strdup.c \
	./src/libft/ft_striteri.c \
	./src/libft/ft_strjoin.c \
	./src/libft/ft_strlcat.c \
	./src/libft/ft_strlcpy.c \
	./src/libft/ft_strlen.c \
	./src/libft/ft_strmapi.c \
	./src/libft/ft_strncmp.c \
	./src/libft/ft_strncpy.c \
	./src/libft/ft_strnstr.c \
	./src/libft/ft_strrchr.c \
	./src/libft/ft_strtrim.c \
	./src/libft/ft_substr.c \
	./src/libft/ft_tolower.c \
	./src/libft/ft_toupper.c \
	./src/libft/is_whitespace.c

SRCS = $(FT_PRINTF_SRCS) $(GNL_SRCS) $(LIBFT_SRCS)
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

