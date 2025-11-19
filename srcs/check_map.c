/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:21:12 by mpoirier          #+#    #+#             */
/*   Updated: 2025/11/19 19:07:11 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || is_player(c));
}

static int	find_player(t_game *game)
{
	int	i;
	int	j;
	int	player_count;

	player_count = 0;
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (!is_valid_char(game->map.grid[i][j]))
				return (0);
			if (is_player(game->map.grid[i][j]))
			{
				game->map.player_x = j;
				game->map.player_y = i;
				game->map.player_dir = game->map.grid[i][j];
				player_count++;
			}
			j++;
		}
		i++;
	}
	return (player_count == 1);
}

int	check_map(t_game *game)
{
	if (!game->texture.north || !game->texture.south || !game->texture.west
		|| !game->texture.east)
		return (0);
	if (game->floor.hex == -1 || game->ceiling.hex == -1)
		return (0);
	if (!game->map.grid || game->map.height == 0 || game->map.width == 0)
		return (0);
	if (!find_player(game))
		return (0);
	if (!validate_map_walls(game))
		return (0);
	return (1);
}
