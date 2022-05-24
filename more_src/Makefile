SRC_FILES= 		echo.c \
				pwd.c \
				ft_str_check.c \
				signal.c


SRC=$(addprefix built-ins/, $(SRC_FILES))
OBJ=$(addprefix obj/, $(SRC_FILES:.c=.o))
OBJ_DIR=obj
LIBFT=../librarie/libft/libft.a
LIBFT_DIR=../librarie/libft
NAME=minishell

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJ)
	gcc -Wall -Werror -Wextra $(OBJ) $(LIBFT) -o $(NAME) -lreadline

obj/%.o: sources/%.c
	gcc -Wall -Werror -Wextra -c $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re