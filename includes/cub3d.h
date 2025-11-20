/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:55:27 by bozil             #+#    #+#             */
/*   Updated: 2025/11/20 00:12:42 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "keys.h"
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 720
# define TEX_WIDTH 64
# define TEX_HEIGHT 64
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.03

typedef struct s_img
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_texture
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	t_img		tex[4];
}				t_texture;

typedef struct s_color
{
	int			r;
	int			g;
	int			b;
	int			hex;
}				t_color;

typedef struct s_map
{
	char		**grid;
	int			width;
	int			height;
	int			player_x;
	int			player_y;
	char		player_dir;
}				t_map;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_map		map;
	t_player	player;
	t_texture	texture;
	t_color		floor;
	t_color		ceiling;
}				t_game;

// parse_map
int				parse_file(const char *file, t_game *game);

// parse_texture
int				parse_texture_line(char *line, t_game *game);
int				identify_texture_type(char *line, char **path_out);

// parse_texture
int				get_texture_type(char *line, int *i);
int				check_duplicate(t_game *game, int type);
void			clean_path(char *path);
void			store_texture(t_game *game, int type, char *texture_path);

// parse_texture_utils
int				get_texture_type(char *line, int *i);
int				check_duplicate(t_game *game, int type);
void			store_texture(t_game *game, int type, char *texture_path);
void			clean_path(char *path);

// parse_color
int				parse_color_line(char *line, t_game *game);

// parse_color_utils
int				get_color_type(char *line, int *i);
int				validate_rgb_range(int r, int g, int b);
int				check_color_duplicate(t_game *game, int type);
void			store_color(t_game *game, int type, int r, int g, int b);
char			**split_rgb_values(char *rgb_str);

// utils
int				is_space(char c);
void			free_split(char **split);
char			*ft_strtrim_whitespace(char *str);

// parse_grid
int				parse_map_grid(char **lines, t_game *game, int start_index);

// parse_grid_utils
int				is_empty_line(char *line);
int				allocate_map_grid(t_game *game);
int				fill_map_grid(char **lines, t_game *game, int start);

// check_map
int				check_map(t_game *game);

#endif