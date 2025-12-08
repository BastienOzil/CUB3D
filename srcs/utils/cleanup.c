/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:30:00 by bozil             #+#    #+#             */
/*   Updated: 2025/11/24 13:40:18 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Libère toute la mémoire: chemins des textures, grille 2D de la map 
 * et autres allocations dynamiques.
 */

#include "../includes/cub3d.h"

static void	free_map(t_game *game)
{
	int	i;

	if (game->map.grid)
	{
		i = 0;
		while (i < game->map.height)
		{
			if (game->map.grid[i])
				free(game->map.grid[i]);
			i++;
		}
		free(game->map.grid);
		game->map.grid = NULL;
	}
}

void	free_game(t_game *game)
{
	if (game->texture.north)
		free(game->texture.north);
	if (game->texture.south)
		free(game->texture.south);
	if (game->texture.west)
		free(game->texture.west);
	if (game->texture.east)
		free(game->texture.east);
	free_map(game);
}
