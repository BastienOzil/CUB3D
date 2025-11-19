/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:50:21 by bozil             #+#    #+#             */
/*   Updated: 2025/11/19 20:50:28 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_texture_type(char *line, int *i)
{
	if (ft_strncmp(&line[*i], "NO", 2) == 0)
		return (0);
	else if (ft_strncmp(&line[*i], "SO", 2) == 0)
		return (1);
	else if (ft_strncmp(&line[*i], "EA", 2) == 0)
		return (2);
	else if (ft_strncmp(&line[*i], "WE", 2) == 0)
		return (3);
	return (-1);
}

void	clean_path(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len > 0 && path[len - 1] == '\n')
		path[len - 1] = '\0';
	len = ft_strlen(path);
	while (len > 0 && is_space(path[len - 1]))
	{
		path[len - 1] = '\0';
		len--;
	}
}

int	check_duplicate(t_game *game, int type)
{
	if (type == 0 && game->texture.north != NULL)
		return (1);
	if (type == 1 && game->texture.south != NULL)
		return (1);
	if (type == 2 && game->texture.east != NULL)
		return (1);
	if (type == 3 && game->texture.west != NULL)
		return (1);
	return (0);
}

void	store_texture(t_game *game, int type, char *texture_path)
{
	if (type == 0)
		game->texture.north = texture_path;
	else if (type == 1)
		game->texture.south = texture_path;
	else if (type == 2)
		game->texture.east = texture_path;
	else if (type == 3)
		game->texture.west = texture_path;
}
