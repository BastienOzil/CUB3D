/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:57:09 by mpoirier          #+#    #+#             */
/*   Updated: 2025/11/17 15:19:52 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int is_valid_extension(const char *filename)
{
    size_t len;
    len = ft_strlen(filename);
    if (len < 4 || ft_strcmp(&filename[len - 4], ".cub") != 0)
        return (0);
    return (1);
}

static int read_lines(int fd, char **content)
{
    char *line;
    char *tmp;
    
    line = get_next_line(fd);
    while (line)
    {
        tmp = ft_strjoin(*content, line);
        free(*content);
        free(line);
        if (!tmp)
            return (0);
        *content = tmp;
        line = get_next_line(fd);
    }
    return (1);
}

static int read_map_file(const char *file, char **content)
{
    int fd;
    
    *content = ft_strdup("");
    if (!*content)
        return (0);
    fd = open(file, O_RDONLY);
    if (fd < 0)
        return (0);
    if (!read_lines(fd, content))
    {
        close(fd);
        return (0);
    }
    close(fd);
    return (1);
}

static int convert_to_grid(t_map *map, const char *content)
{
    map->grid = ft_split(content, '\n');
    if (!map->grid)
        return (0);
    map->height = 0;
    while (map->grid[map->height])
        (map->height)++;
    map->width = ft_strlen(map->grid[0]);
    return (1);
}

int parse_map(const char *file, t_map *map)
{
    char *content;
    if (!is_valid_extension(file))
        return (0);
    if (!read_map_file(file, &content))
        return (0);
    if (!convert_to_grid(map, content))
    {
        free(content);
        return (0);
    }
    free(content);
    if (!check_map(map))
    {
        free_map(map);
        return (0);
    }
    return (1);
}