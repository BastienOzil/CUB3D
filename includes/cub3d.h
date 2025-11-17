/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:55:27 by bozil             #+#    #+#             */
/*   Updated: 2025/11/17 15:27:08 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "../minilibx-linux/mlx.h"
#include "../libft/libft.h"
#include "keys.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		ennemies;
	int		exits;
	int		player_start;
	int		player_x;
	int		player_y;
}			t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_map	map;
	int		player_x;
	int		player_y;
	int		moves;
	void	*wall_img;
	void	*floor_img;
	void	*exit_img;
	void	*item_img;
	void	*player_img;
}			t_game;

int main(int argc, char **argv);
int parse_map(const char *file, t_map *map);
int check_map(t_map *map);

#define TILE_SIZE 64
#endif