NAME		= a.out

CC		= gcc
CFLAGS		= -Wall -Wextra
VG_FLAGS	= --tool=drd --tool=helgrind
INC		= ./includes

VPATH		= srcs
OBJ_DIR		= obj

SRCS		= main.c \
		  utils.c \
		  ft_lstnew.c \
		  ft_lstlast.c \
		  ft_lstadd_back.c \

OBJS		= $(addprefix obj/, $(SRCS:.c=.o))

all: $(NAME)

mkdir:
	mkdir -p $(OBJ_DIR) 

obj/%.o: %.c  mkdir
	$(CC) $(CLAGS) -I$(INC) -c $< -o $@

$(NAME): $(OBJS)
	@echo "Compile Philophers"
	$(CC) $^ -o $@

vg:
	@echo "Valgrind Philophers"
	valgrind $(VG_FLAGS) ./$(NAME)

clean:
	@echo "Clean Philophers" 
	@rm -rf $(OBJS)

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all clean fclean re
