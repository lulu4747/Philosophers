NAME			= philo

SRCS			= death.c
SRCS			+= life.c
SRCS			+= main.c
SRCS			+= parsing.c
SRCS			+= philosophy.c

OBJ_DIR			= ./srcs/obj/
PHILO_DIR		= ./srcs/philo/

LIBFT_DIR		= ./srcs/libft/
LIBFT_A			= $(addprefix $(LIBFT_DIR), libft.a)
OBJ				= $(addprefix $(OBJ_DIR),$(SRCS:.c=.o))
INC				= ./srcs/philo/philo.h

CC				= gcc
CFLAGS			= -Wall -Werror -Wextra
P_THREAD		= -pthread
RM				= rm -f
RM_DIR			= rm -rf

all:
	mkdir -p $(OBJ_DIR)
	make -C $(LIBFT_DIR) --no-print-directory
	$(MAKE) $(NAME) --no-print-directory

$(OBJ_DIR)%.o:$(PHILO_DIR)%.c $(INC)
	$(CC) $(CFLAGS) $(P_THREAD) -c $< -o $@

$(NAME):$(OBJ) $(INC) $(LIBFT_A)
	$(CC) $(CFLAGS) $(P_THREAD) $(OBJ) $(LIBFT_A) -o $(NAME)

clean:
	$(RM_DIR) $(OBJ_DIR)
	$(RM_DIR) $(OBJ_DIR_BONUS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean:
	$(RM_DIR) $(OBJ_DIR)
	$(RM) $(NAME)
	$(RM_DIR) $(OBJ_DIR_BONUS)
	$(RM) $(NAME_BONUS)
	$(MAKE) fclean -C $(LIBFT_DIR)

NAME_BONUS		= philo_bonus

SRCS_BONUS		= main.c
SRCS_BONUS		+= parsing.c
SRCS_BONUS		+= philosophy.c

BONUS_DIR		= ./srcs/philo_bonus/
OBJ_DIR_BONUS	= ./srcs/obj_bonus/

OBJ_BONUS		= $(addprefix $(OBJ_DIR_BONUS),$(SRCS_BONUS:.c=.o))
INC_BONUS		= ./srcs/philo_bonus/philo_bonus.h

bonus:all
	mkdir -p $(OBJ_DIR_BONUS)
	$(MAKE) $(NAME_BONUS) --no-print-directory

$(OBJ_DIR_BONUS)%.o:$(BONUS_DIR)%.c $(INC_BONUS)
	$(CC) $(CFLAGS) $(P_THREAD) -c $< -o $@

$(NAME_BONUS):$(OBJ_BONUS) $(INC_BONUS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(P_THREAD) $(OBJ_BONUS) $(LIBFT_A) -o $(NAME_BONUS)

re:fclean all

re_bonus:fclean bonus

.PHONY:all clean fclean bonus re re_bonus
