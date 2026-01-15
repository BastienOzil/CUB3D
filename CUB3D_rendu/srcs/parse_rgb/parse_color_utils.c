/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 23:45:00 by bozil             #+#    #+#             */
/*   Updated: 2025/11/24 13:40:26 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Utility functions: identify type, validate RGB range,
 * check for duplicates.
 */

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
