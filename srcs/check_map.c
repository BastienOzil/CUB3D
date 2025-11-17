/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:21:12 by mpoirier          #+#    #+#             */
/*   Updated: 2025/11/17 15:27:50 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void initialize_map_elements(t_map *map)
{
    map->ennemies = 0;
    map->exits = 0;
    map->player_start = 0;
}

int check_map(t_map *map)
{
    initialize_map_elements(map);
    if (!is_rectangular(map))
        return (0);
    if (!is_surrounded_by_walls(map))
        return (0);
    if (!parse_map_grid(map))
        return (0);
    return (map->ennemies > 0 && map->exits == 1 && map->player_start == 1);
}
