.SILENT:

NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRC_DIR = srcs

OBJ_DIR = objs

MLX_DIR = minilibx-linux

LIBFT_DIR = libft

SRCS = $(SRC_DIR)/game/init_game.c \
       $(SRC_DIR)/game/load_textures.c \
       $(SRC_DIR)/game/main.c \
       $(SRC_DIR)/game/start_game.c \
       $(SRC_DIR)/keyboard/movements.c \
       $(SRC_DIR)/keyboard/movements_keys.c \
       $(SRC_DIR)/parse_map/check_map.c \
       $(SRC_DIR)/parse_map/flood_fill.c \
       $(SRC_DIR)/parse_map/parse_grid.c \
       $(SRC_DIR)/parse_map/parse_grid_check.c \
       $(SRC_DIR)/parse_map/parse_grid_utils.c \
       $(SRC_DIR)/parse_map/parse_map.c \
       $(SRC_DIR)/parse_map/split_lines.c \
       $(SRC_DIR)/parse_rgb/parse_color.c \
       $(SRC_DIR)/parse_rgb/parse_color_split.c \
       $(SRC_DIR)/parse_rgb/parse_color_store.c \
       $(SRC_DIR)/parse_rgb/parse_color_utils.c \
       $(SRC_DIR)/parse_rgb/parse_texture.c \
       $(SRC_DIR)/parse_rgb/parse_texture_utils.c \
       $(SRC_DIR)/raycasting/raycasting.c \
       $(SRC_DIR)/raycasting/raycasting_utils.c \
       $(SRC_DIR)/utils/cleanup.c \
       $(SRC_DIR)/utils/error.c \
       $(SRC_DIR)/utils/utils.c

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
	@mkdir -p $(OBJ_DIR)/game
	@mkdir -p $(OBJ_DIR)/keyboard
	@mkdir -p $(OBJ_DIR)/parse_map
	@mkdir -p $(OBJ_DIR)/parse_rgb
	@mkdir -p $(OBJ_DIR)/raycasting
	@mkdir -p $(OBJ_DIR)/utils

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