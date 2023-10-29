NAME		= philo

CC		= gcc -g -pthread
CFLAGS		= -Wall -Wextra -Werror

INC		= ./includes

VPATH		= srcs
OBJ_DIR		= obj

SRCS		= main.c \
		  check_args.c \
		  init_data.c \
		  threads.c\
		  action.c \
		  routine.c \
		  utils.c \
		  error.c \
		  free_data.c \
		  ft_isdigit.c \
		  ft_strlen.c \
		  ft_strdup.c \
		  ft_atoi.c \
		  ft_bzero.c \
		  ft_calloc.c \
		  ft_atoi.c \

OBJS		= $(addprefix obj/, $(SRCS:.c=.o))

ifeq ($(DEBUG), 1)
CFLAGS	+= -fsanitize=thread
endif

all: $(NAME)

obj/%.o: %.c  
	@if [ ! -d $(OBJ_DIR) ]; then \
		echo mkdir $(OBJ_DIR); \
		mkdir -p $(OBJ_DIR); \
	fi
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

$(NAME): $(OBJS)
	@echo "Compile Philophers"
	$(CC) $(CFLAGS) $^ -o $@
clean:
	@echo "Clean Philophers" 
	@rm -rf $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re 
