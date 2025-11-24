/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 09:46:47 by bozil             #+#    #+#             */
/*   Updated: 2025/11/24 13:40:22 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Vérifie que tous les espaces accessibles (0 et joueur) sont entourés 
 * de murs en validant les 4 cases adjacentes.
 */

#include "../includes/cub3d.h"

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_valid_position(t_game *game, int y, int x)
{
	int	line_len;

	if (y < 0 || y >= game->map.height)
		return (0);
	if (x < 0)
		return (0);
	line_len = ft_strlen(game->map.grid[y]);
	if (x >= line_len)
		return (0);
	if (game->map.grid[y][x] == ' ')
		return (0);
	return (1);
}

static int	check_cell_surroundings(t_game *game, int y, int x)
{
	if (!is_valid_position(game, y - 1, x))
		return (0);
	if (!is_valid_position(game, y + 1, x))
		return (0);
	if (!is_valid_position(game, y, x - 1))
		return (0);
	if (!is_valid_position(game, y, x + 1))
		return (0);
	return (1);
}

int	validate_map_walls(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (game->map.grid[i][j] == '0' || is_player(game->map.grid[i][j]))
			{
				if (!check_cell_surroundings(game, i, j))
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
