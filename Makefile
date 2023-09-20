NAME		= a.out

CC		= gcc -g
CFLAGS		= -Wall -Wextra
VG		= valgrind --tool=drd --tool=helgrind

VPATH		= srcs
OBJ_DIR		= obj

SRCS		= main.c
OBJS		= $(addprefix obj/, $(SRCS:.c=.o))

all: $(NAME)

mkdir:
	mkdir -p $(OBJ_DIR) 

obj/%.o: %.c  mkdir
	$(CC) $(CLAGS) -c $< -o $@

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
