/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:57:09 by mpoirier          #+#    #+#             */
/*   Updated: 2025/11/19 20:44:22 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	char	*line;
	char	*content;
	char	*tmp;

	content = ft_strdup("");
	if (!content)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		tmp = ft_strjoin(content, line);
		free(content);
		free(line);
		if (!tmp)
			return (NULL);
		content = tmp;
		line = get_next_line(fd);
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
		if (!parse_texture_line(trimmed, game)
			&& !parse_color_line(trimmed, game))
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
	if (!parse_lines(lines, game, &map_started))
	{
		free_split(lines);
		return (0);
	}
	free_split(lines);
	return (1);
}
