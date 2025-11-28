/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:56:46 by bozil             #+#    #+#             */
/*   Updated: 2025/11/28 13:51:39 by mpoirier         ###   ########.fr       */
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

t_wall init_wall(t_ray *ray, t_player player)
{
    t_wall wall;
    double dist;
    
    if (ray->side == 0)
        dist = (ray->map_x - player.pos_x + (1 - ray->step_x) / 2) / ray->dir_x;
    else
        dist = (ray->map_y - player.pos_y + (1 - ray->step_y) / 2) / ray->dir_y;
    wall.height = (int)(SCREEN_WIDTH / dist);
    wall.start = -wall.height / 2 + SCREEN_HEIGHT / 2;
    if (wall.start < 0)
        wall.start = 0;
    wall.end = wall.height / 2 + SCREEN_HEIGHT / 2;
    if (wall.end >= SCREEN_HEIGHT)
        wall.end = SCREEN_HEIGHT - 1;
    wall.dist = dist;
    return (wall);
}
int get_texture_num(t_ray *ray)
{
    if (ray->side == 0)  // Mur VERTICAL (Est ou Ouest)
    {
        if (ray->dir_x > 0)
            return (3);  // Est (EA)
        else
            return (2);  // Ouest (WE)
    }
    else  // Mur HORIZONTAL (Nord ou Sud)
    {
        if (ray->dir_y > 0)
            return (1);  // Sud (SO)
        else
            return (0);  // Nord (NO)
    }
}

void draw_line(int x, t_ray ray, t_game *game, t_wall wall)
{
    for (int y = 0; y < wall.start; y++)
        put_pixel(x, y, game->ceiling.hex);
    int tex_num = get_texture_num(&ray);
    double wallE;
    if (ray.side == 0)
        wallE = game->player.pos_y + wall.dist * ray.dir_y;
    else
        wallE = game->player.pos_x + wall.dist * ray.dir_x;
    wallE -= floor(wallE);
    int tex_x = (int)(wallE * TEX_WIDTH);
    if ((ray.side == 0 && ray.dir_x > 0) || (ray.side == 1 && ray.dir_y < 0))
        tex_x = TEX_WIDTH - tex_x - 1;
    for (int y = wall.start; y < wall.end; y++)
    {
        int d = y * 256 - SCREEN_HEIGHT * 128 + wall.height * 128;
        int tex_y = ((d * TEX_HEIGHT) / wall.height) / 256 ;
        int color = get_texture_color(game->texture.tex[tex_num], tex_x, tex_y);
        put_pixel(x, y, color);
    }
    for (int y = wall.end; y < SCREEN_HEIGHT; y++)
        put_pixel(x, y, game->floor.hex);
}

void	raycasting(t_game *game)
{
	t_ray   ray;
    t_wall  wall;
	int     x;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		ray = init_ray(x, game->player);
        perform_dda(&ray, game);
        wall = init_wall(&ray, game->player);
        draw_line(x, ray, game, wall);
	}
}