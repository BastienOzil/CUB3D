/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:55:27 by bozil             #+#    #+#             */
/*   Updated: 2025/11/19 19:07:02 by bozil            ###   ########.fr       */
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

typedef struct s_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_ray;

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

/* Parsing */
int				parse_file(const char *file, t_game *game);
int				parse_texture_line(char *line, t_game *game);
int				parse_color_line(char *line, t_game *game);
int				parse_map_grid(char **lines, t_game *game, int start);
int				check_map(t_game *game);
int				validate_map_walls(t_game *game);

/* Utils */
int				ft_isspace(char c);
char			*ft_strtrim_whitespace(char *str);
int				create_rgb(int r, int g, int b);
void			free_split(char **split);
int				ft_error(char *msg);

/* Game */
void			init_game(t_game *game);
int				start_game(t_game *game);
void			init_player(t_game *game);
int				load_textures(t_game *game);

/* Raycasting */
void			raycasting(t_game *game);
void			init_ray(t_game *game, t_ray *ray, int x);
void			perform_dda(t_game *game, t_ray *ray);
void			calculate_wall_distance(t_ray *ray);
void			draw_vertical_line(t_game *game, t_ray *ray, int x);

/* Controls */
int				key_press(int keycode, t_game *game);
int				close_game(t_game *game);
void			move_forward(t_game *game);
void			move_backward(t_game *game);
void			rotate_left(t_game *game);
void			rotate_right(t_game *game);

/* Cleanup */
void			free_game(t_game *game);
void			free_map(t_map *map);

#endif