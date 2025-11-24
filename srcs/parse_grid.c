/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 23:52:28 by bozil             #+#    #+#             */
/*   Updated: 2025/11/24 13:40:31 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Parse la grille de la map: localise le début, calcule les dimensions, 
 * alloue la mémoire et remplit en gérant les maps rectangulaires.
 */

#include "../includes/cub3d.h"

static int	find_map_start(char **lines, int start_index)
{
	int	i;

	if (start_index < 0)
		start_index = 0;
	i = start_index;
	while (lines[i])
	{
		if (lines[i][0] == '\0' || is_empty_line(lines[i]))
		{
			i++;
			continue ;
		}
		if (ft_strchr(lines[i], '0') || ft_strchr(lines[i], '1'))
			return (i);
		i++;
	}
	return (-1);
}

static int	calculate_map_dimensions(char **lines, int start, t_game *game)
{
	int	height;
	int	max_width;
	int	line_len;

	height = 0;
	max_width = 0;
	while (lines[start + height])
	{
		line_len = ft_strlen(lines[start + height]);
		if (line_len > max_width)
			max_width = line_len;
		height++;
	}
	if (height == 0 || max_width == 0)
		return (0);
	game->map.height = height;
	game->map.width = max_width;
	return (1);
}

int	parse_map_grid(char **lines, t_game *game, int start_index)
{
	int	map_start;

	map_start = find_map_start(lines, start_index);
	if (map_start == -1)
		return (0);
	if (!calculate_map_dimensions(lines, map_start, game))
		return (0);
	if (!allocate_map_grid(game))
		return (0);
	if (!fill_map_grid(lines, game, map_start))
		return (0);
	return (1);
}