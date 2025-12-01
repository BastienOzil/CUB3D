/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:22:28 by bozil             #+#    #+#             */
/*   Updated: 2025/12/01 10:21:34 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Initialise la structure game et calcule la position/direction du joueur 
 * avec vecteur de direction et plan de caméra selon l'orientation.
 */

#include "../includes/cub3d.h"

void	init_game(t_game *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->img.img = NULL;
	game->map.grid = NULL;
	game->map.width = 0;
	game->map.height = 0;
	game->map.player_x = -1;
	game->map.player_y = -1;
	game->map.player_dir = '\0';
	game->texture.north = NULL;
	game->texture.south = NULL;
	game->texture.west = NULL;
	game->texture.east = NULL;
	game->floor.hex = -1;
	game->ceiling.hex = -1;
	game->player.pos_x = 0;
	game->player.pos_y = 0;
	game->player.dir_x = 0;
	game->player.dir_y = 0;
	game->player.plane_x = 0;
	game->player.plane_y = 0;
	ft_memset(game->keys, 0, sizeof(game->keys));
}

static void	set_vertical_direction(t_game *game)
{
	game->player.dir_x = 0;
	if (game->map.player_dir == 'N')
	{
		game->player.dir_y = -1;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (game->map.player_dir == 'S')
	{
		game->player.dir_y = 1;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
}

static void	set_horizontal_direction(t_game *game)
{
	game->player.dir_y = 0;
	game->player.plane_y = 0.66;
	if (game->map.player_dir == 'E')
	{
		game->player.dir_x = 1;
		game->player.plane_x = 0;
	}
	else if (game->map.player_dir == 'W')
	{
		game->player.dir_x = -1;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

void	init_player(t_game *game)
{
	game->player.pos_x = game->map.player_x + 0.5;
	game->player.pos_y = game->map.player_y + 0.5;
	if (game->map.player_dir == 'N' || game->map.player_dir == 'S')
		set_vertical_direction(game);
	else if (game->map.player_dir == 'E' || game->map.player_dir == 'W')
		set_horizontal_direction(game);
}
