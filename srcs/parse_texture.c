/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 19:49:42 by bozil             #+#    #+#             */
/*   Updated: 2025/11/24 13:40:34 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Parse les lignes de textures (NO/SO/WE/EA): identifie le type, extrait 
 * le chemin .xpm, vérifie l'existence et détecte les doublons.
 */

#include "../includes/cub3d.h"

int	identify_texture_type(char *line, char **path_out)
{
	int	i;
	int	type;

	i = 0;
	while (is_space(line[i]))
		i++;
	type = get_texture_type(line, &i);
	if (type == -1)
		return (-1);
	i += 2;
	while (is_space(line[i]))
		i++;
	*path_out = &line[i];
	clean_path(*path_out);
	return (type);
}

int	parse_texture_line(char *line, t_game *game)
{
	char	*path;
	char	*texture_path;
	int		type;
	int		fd;

	type = identify_texture_type(line, &path);
	if (type == -1 || check_duplicate(game, type))
		return (1);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (1);
	close(fd);
	texture_path = ft_strdup(path);
	if (!texture_path)
		return (1);
	store_texture(game, type, texture_path);
	return (0);
}
