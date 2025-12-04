/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 00:15:00 by bozil             #+#    #+#             */
/*   Updated: 2025/11/24 13:40:29 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Fonctions utilitaires: vérifier lignes vides, allouer et remplir 
 * la grille 2D avec espaces et contenu.
 */

#include "../includes/cub3d.h"

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!is_space(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	allocate_map_grid(t_game *game)
{
	int	i;

	game->map.grid = (char **)malloc(sizeof(char *) * (game->map.height + 1));
	if (!game->map.grid)
		return (0);
	i = 0;
	while (i <= game->map.height)
	{
		game->map.grid[i] = NULL;
		i++;
	}
	return (1);
}

static void	fill_line_with_spaces(char *line, int width)
{
	int	i;

	i = 0;
	while (i < width)
	{
		line[i] = ' ';
		i++;
	}
	line[width] = '\0';
}

static void	copy_line_content(char *dest, char *src, int max_width)
{
	int	i;

	i = 0;
	while (src[i] && i < max_width)
	{
		dest[i] = src[i];
		i++;
	}
}

int	fill_map_grid(char **lines, t_game *game, int start)
{
	int	i;

	i = 0;
	while (i < game->map.height)
	{
		game->map.grid[i] = malloc(sizeof(char) * (game->map.width + 1));
		if (!game->map.grid[i])
			return (0);
		fill_line_with_spaces(game->map.grid[i], game->map.width);
		copy_line_content(game->map.grid[i], lines[start + i], game->map.width);
		i++;
	}
	game->map.grid[game->map.height] = NULL;
	return (1);
}
