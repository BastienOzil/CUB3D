/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:22:35 by bozil             #+#    #+#             */
/*   Updated: 2025/11/24 13:40:24 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Charge les 4 textures XPM en mémoire avec mlx_xpm_file_to_image() 
 * et récupère leurs adresses pour le rendu.
 */

#include "../includes/cub3d.h"

static int	load_single_texture(t_game *game, t_img *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, path,
			&texture->width, &texture->height);
	if (!texture->img)
		return (0);
	texture->addr = mlx_get_data_addr(texture->img,
			&texture->bits_per_pixel,
			&texture->line_length,
			&texture->endian);
	if (!texture->addr)
	{
		mlx_destroy_image(game->mlx, texture->img);
		return (0);
	}
	return (1);
}

int	load_textures(t_game *game)
{
	if (!load_single_texture(game, &game->texture.tex[0], game->texture.north))
		return (0);
	if (!load_single_texture(game, &game->texture.tex[1], game->texture.south))
		return (0);
	if (!load_single_texture(game, &game->texture.tex[2], game->texture.west))
		return (0);
	if (!load_single_texture(game, &game->texture.tex[3], game->texture.east))
		return (0);
	return (1);
}
