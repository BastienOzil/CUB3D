/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:56:46 by bozil             #+#    #+#             */
/*   Updated: 2025/11/28 13:06:26 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_ray side(t_ray ray, t_player player)
{
    if (ray.dir_x < 0)
    {
        ray.step_x = -1;
        ray.side_dist_x = (player.pos_x - ray.map_x) * ray.delta_x;
    }
    else
    {
        ray.step_x = 1;
        ray.side_dist_x = (ray.map_x + 1.0 - player.pos_x) * ray.delta_x;
    }
    if (ray.dir_y < 0)
    {
        ray.step_y = -1;
        ray.side_dist_y = (player.pos_y - ray.map_y) * ray.delta_y;
    }
    else
    {
        ray.step_y = 1;
        ray.side_dist_y = (ray.map_y + 1.0 - player.pos_y) * ray.delta_y;
    }
    return (ray);
}

t_ray init_ray(int x, t_player player)
{
    t_ray ray;
    
    ray.angle = 2 * x / (double)SCREEN_WIDTH - 1;
    ray.dir_x = player.dir_x + player.plane_x * ray.angle;
    ray.dir_y = player.dir_y + player.plane_y * ray.angle;
    ray.map_x = (int)player.pos_x;
    ray.map_y = (int)player.pos_y;
    ray.delta_x = fabs(1/ ray.dir_x);
    ray.delta_y = fabs(1/ ray.dir_y);
    return(side(ray, player));
}

void perform_dda(t_ray *ray, t_game *game)
{
    int hit;

    hit = 0;
    while (!hit)
    {
        if (ray->side_dist_x <  ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_y;
            ray->map_y;
            ray->side = 1;
        }
        if (is_wall(game->map.grid[ray->map_y][ray->map_x]))
            hit = 1;
    }
}



void	raycasting(t_game *game)
{
	t_ray   ray;
	int     x;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		ray = init_ray(x, game->player);
        perform_dda(&ray, game);
        calculate_wall_distance(&ray, game);
        draw_vertical_line(x, &ray, game);
	}
}