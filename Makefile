NAME		= a.out

CC		= gcc -g -lpthread
CFLAGS		= -Wall -Wextra

#VG_FLAGS	= --tool=drd 
VG_FLAgS	= --tool=helgrind 

INC		= ./includes

VPATH		= srcs
OBJ_DIR		= obj

SRCS		= main.c \
		  init_data.c \
		  utils.c \
		  free_data.c \
		  ft_bzero.c \
		  ft_calloc.c \

OBJS		= $(addprefix obj/, $(SRCS:.c=.o))

all: $(NAME)

mkdir:
	mkdir -p $(OBJ_DIR) 

vg:
	@echo "Valgrind Philophers"
	valgrind $(VG_FLAGS) ./$(NAME)

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
