NAME	= libft.a

SRC		= ft_atoi_secure.c
SRC		+= ft_atoi.c
SRC		+= ft_atol.c
SRC		+= ft_bzero.c
SRC		+= ft_calloc.c
SRC		+= ft_is_digit.c
SRC		+= ft_is_number.c
SRC		+= ft_putchar_fd.c
SRC		+= ft_putstr_fd.c
SRC		+= ft_sort.c
SRC		+= ft_strchr.c
SRC		+= ft_strcmp.c
SRC		+= ft_strdup.c
SRC		+= ft_strjoin.c
SRC		+= ft_strlen.c
SRC		+= ft_substr.c

INC = libft.h
OBJ_DIR = ./obj/
OBJ = $(addprefix $(OBJ_DIR),$(notdir $(SRC:%.c=%.o)))

CC			= gcc
CFLAGS		= -Wall -Werror -Wextra

all:
	mkdir -p $(OBJ_DIR)
	$(MAKE) $(NAME) --no-print-directory

$(OBJ_DIR)%.o : %.c $(INC)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(INC)
	ar rc $(NAME) $(OBJ) $(INC)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY : re fclean clean all