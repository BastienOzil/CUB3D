.SILENT:

NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR = srcs

OBJ_DIR = objs

MLX_DIR = minilibx-linux

LIBFT_DIR = libft

SRCS = $(SRC_DIR)/check_map.c \
       $(SRC_DIR)/cleanup.c \
       $(SRC_DIR)/error.c \
       $(SRC_DIR)/flood_fill.c \
       $(SRC_DIR)/init_game.c \
       $(SRC_DIR)/load_textures.c \
       $(SRC_DIR)/main.c \
       $(SRC_DIR)/parse_color.c \
       $(SRC_DIR)/parse_color_utils.c \
       $(SRC_DIR)/parse_grid.c \
       $(SRC_DIR)/parse_grid_utils.c \
       $(SRC_DIR)/parse_map.c \
       $(SRC_DIR)/parse_texture.c \
       $(SRC_DIR)/parse_texture_utils.c \
       $(SRC_DIR)/start_game.c \
       $(SRC_DIR)/utils.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

MLX = $(MLX_DIR)/libmlx_Linux.a

LIBFT = $(LIBFT_DIR)/libft.a

MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz

INCLUDES = -I./includes -I$(MLX_DIR) -I$(LIBFT_DIR)

all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re