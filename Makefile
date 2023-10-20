NAME		= a.out

CC		= gcc -g -lpthread
CFLAGS		= -Wall -Wextra

VG_FLAGS	= --tool=drd 
#VG_FLAgS	= --tool=helgrind 

INC		= ./includes

VPATH		= srcs
OBJ_DIR		= obj

SRCS		= main.c \
		  check_args.c \
		  init_data.c \
		  threads.c\
		  routine.c \
		  utils.c \
		  error.c \
		  free_data.c \
		  ft_strlen.c \
		  ft_strdup.c \
		  ft_atoi.c \
		  ft_bzero.c \
		  ft_calloc.c \
		  ft_atoi.c \

OBJS		= $(addprefix obj/, $(SRCS:.c=.o))

ifeq ($(DEBUG), 1)
CFLAG	+= fsanitze=thread
endif

all: $(NAME)

mkdir:
	mkdir -p $(OBJ_DIR) 

vg:
	@echo "Valgrind Philophers"
	valgrind $(VG_FLAGS) ./$(NAME) 3 100 100 100 2

obj/%.o: %.c  mkdir
	$(CC) $(CLAGS) -I$(INC) -c $< -o $@

$(NAME): $(OBJS)
	@echo "Compile Philophers"
	$(CC) $^ -o $@
clean:
	@echo "Clean Philophers" 
	@rm -rf $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re 
