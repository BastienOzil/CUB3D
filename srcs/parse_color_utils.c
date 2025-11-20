/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 23:45:00 by bozil             #+#    #+#             */
/*   Updated: 2025/11/19 23:43:33 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_color_type(char *line, int *i)
{
	while (is_space(line[*i]))
		(*i)++;
	if (line[*i] == 'F')
		return (0);
	else if (line[*i] == 'C')
		return (1);
	return (-1);
}

int	validate_rgb_range(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (0);
	return (1);
}

int	check_color_duplicate(t_game *game, int type)
{
	if (type == 0 && game->floor.hex != -1)
		return (1);
	if (type == 1 && game->ceiling.hex != -1)
		return (1);
	return (0);
}

void	store_color(t_game *game, int type, int r, int g, int b)
{
	int	hex;

	hex = (r << 16) | (g << 8) | b;
	if (type == 0)
	{
		game->floor.r = r;
		game->floor.g = g;
		game->floor.b = b;
		game->floor.hex = hex;
	}
	else
	{
		game->ceiling.r = r;
		game->ceiling.g = g;
		game->ceiling.b = b;
		game->ceiling.hex = hex;
	}
}

char	**split_rgb_values(char *rgb_str)
{
	char	**rgb_split;
	int		count;

	rgb_split = ft_split(rgb_str, ',');
	if (!rgb_split)
		return (NULL);
	count = 0;
	while (rgb_split[count])
		count++;
	if (count != 3)
	{
		free_split(rgb_split);
		return (NULL);
	}
	return (rgb_split);
}
