/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_store.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:03:34 by bozil             #+#    #+#             */
/*   Updated: 2025/12/08 14:16:35 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Stockage des couleurs dans la structure game.
 */

#include "../includes/cub3d.h"

static void	store_floor_color(t_game *game, int hex, int rgb[3])
{
	game->floor.r = rgb[0];
	game->floor.g = rgb[1];
	game->floor.b = rgb[2];
	game->floor.hex = hex;
}

static void	store_ceiling_color(t_game *game, int hex, int rgb[3])
{
	game->ceiling.r = rgb[0];
	game->ceiling.g = rgb[1];
	game->ceiling.b = rgb[2];
	game->ceiling.hex = hex;
}

void	store_color(t_game *game, int type, int rgb[3])
{
	int	hex;

	hex = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	if (type == 0)
		store_floor_color(game, hex, rgb);
	else
		store_ceiling_color(game, hex, rgb);
}
