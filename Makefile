CC = gcc
NAME = so_long
SRC = 	main.c \
		map_validation.c \
		path_validation.c \
		ft_utils.c \
		get_next_line.c \
		get_next_line_utils.c
OBJ = $(SRC:.c=.o)
# FLAGS = -Wall -Wextra -Werror
MLX_PATH = mlx_linux

vpath %.c sources get_next_line

# Updated compilation rule with proper flags
%.o: %.c
	$(CC) $(FLAGS) -I/usr/include -I$(MLX_PATH) -c $< -o $@

# Fixed linking command to use correct path and library name
$(NAME): mlx $(OBJ)
	$(CC) -g -O0 $(OBJ) -L$(MLX_PATH) -lmlx_Linux -L/usr/lib -I$(MLX_PATH) -lXext -lX11 -lm -lz -o $(NAME)

mlx:
	@make -C $(MLX_PATH)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

all: $(NAME)

.PHONY: all clean fclean re mlx