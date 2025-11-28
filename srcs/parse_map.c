/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:57:09 by mpoirier          #+#    #+#             */
/*   Updated: 2025/11/28 09:32:57 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Lit et parse le fichier .cub: vérifie l'extension, lit le contenu, 
 * identifie les textures/couleurs et la grille de la map.
 */

#include "../includes/cub3d.h"

static int	is_valid_extension(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	if (ft_strncmp(&filename[len - 4], ".cub", 4) != 0)
		return (0);
	return (1);
}

static char	*read_file_content(int fd)
{
	char	buffer[4096];
	char	*content;
	char	*tmp;
	int		bytes_read;

	content = ft_strdup("");
	if (!content)
		return (NULL);
	bytes_read = read(fd, buffer, 4095);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin(content, buffer);
		free(content);
		if (!tmp)
			return (NULL);
		content = tmp;
		bytes_read = read(fd, buffer, 4095);
	}
	if (bytes_read < 0)
	{
		free(content);
		return (NULL);
	}
	return (content);
}

static int	process_line(char *line, t_game *game, int *map_started)
{
	char	*trimmed;

	trimmed = ft_strtrim_whitespace(line);
	if (!trimmed || trimmed[0] == '\0')
	{
		free(trimmed);
		return (1);
	}
	if (!*map_started && (trimmed[0] == '1' || trimmed[0] == '0'))
		*map_started = 1;
	if (!*map_started)
	{
		if (parse_texture_line(trimmed, game)
			&& parse_color_line(trimmed, game))
		{
			free(trimmed);
			return (0);
		}
	}
	free(trimmed);
	return (1);
}

static int	parse_lines(char **lines, t_game *game, int *map_started)
{
	int	i;

	i = 0;
	while (lines[i] && !*map_started)
	{
		if (!process_line(lines[i], game, map_started))
			return (0);
		i++;
	}
	if (!parse_map_grid(lines, game, i - 1))
		return (0);
	return (i);
}

int	parse_file(const char *file, t_game *game)
{
	int		fd;
	char	*content;
	char	**lines;
	int		map_started;
	int		result;

	if (!is_valid_extension(file))
		return (0);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (0);
	content = read_file_content(fd);
	close(fd);
	if (!content)
		return (0);
	lines = ft_split(content, '\n');
	free(content);
	if (!lines)
		return (0);
	map_started = 0;
	result = parse_lines(lines, game, &map_started);
	free_split(lines);
	return (result);
}
