/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:56:46 by bozil             #+#    #+#             */
/*   Updated: 2025/12/03 09:25:51 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if (is_wall(game->map.grid[ray->map_y][ray->map_x]))
            hit = 1;
    }
}

t_wall init_wall(t_ray *ray, t_player player)
{
    t_wall wall;
    
    if (ray->side == 0)
        wall.dist = (ray->map_x - player.pos_x + (1 - ray->step_x) / 2) / ray->dir_x;
    else
        wall.dist = (ray->map_y - player.pos_y + (1 - ray->step_y) / 2) / ray->dir_y;
    wall.height = (int)(SCREEN_HEIGHT / wall.dist);
    wall.start = -wall.height / 2 + SCREEN_HEIGHT / 2;
    if (wall.start < 0)
        wall.start = 0;
    wall.end = wall.height / 2 + SCREEN_HEIGHT / 2;
    if (wall.end >= SCREEN_HEIGHT)
        wall.end = SCREEN_HEIGHT - 1;
    return (wall);
}
void draw_line(int x, t_ray ray, t_game *game, t_wall wall)
{
    int     y;
    int     tex_num;
    double  wallE;
    int     tex_x;
    int     d;
    int     tex_y;
    int     color;

    y = -1;
    while (++y < wall.start)
        my_mlx_pixel_put(&game->img, x, y, game->ceiling.hex);
    tex_num = get_texture_num(&ray);
    if (ray.side == 0)
        wallE = game->player.pos_y + wall.dist * ray.dir_y;
    else
        wallE = game->player.pos_x + wall.dist * ray.dir_x;
    wallE -= floor(wallE);
    tex_x = (int)(wallE * TEX_WIDTH);
    if ((ray.side == 0 && ray.dir_x > 0) || (ray.side == 1 && ray.dir_y < 0))
        tex_x = TEX_WIDTH - tex_x - 1;
    y = wall.start -1 ;
    while (++y < wall.end)
    {
        d = y * 256 - SCREEN_HEIGHT * 128 + wall.height * 128;
        tex_y = ((d * TEX_HEIGHT) / wall.height) / 256;
        color = get_tex_color(&game->texture.tex[tex_num], tex_x, tex_y);
        my_mlx_pixel_put(&game->img, x, y, color);
    }
    while (y < SCREEN_HEIGHT)
        my_mlx_pixel_put(&game->img, x, y++, game->floor.hex);
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
