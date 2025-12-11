/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 10:56:46 by bozil             #+#    #+#             */
/*   Updated: 2025/12/11 10:38:15 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_ray	init_ray(int x, t_player player)
{
	t_ray	ray;

	ray.angle = 2 * x / (double)SCREEN_WIDTH - 1;
	ray.dir_x = player.dir_x + player.plane_x * ray.angle;
	ray.dir_y = player.dir_y + player.plane_y * ray.angle;
	ray.map_x = (int)player.pos_x;
	ray.map_y = (int)player.pos_y;
	ray.delta_x = fabs(1 / ray.dir_x);
	ray.delta_y = fabs(1 / ray.dir_y);
	return (side(ray, player));
}

static t_wall	init_wall(t_ray *ray, t_player player)
{
	t_wall	wall;
	double	perp_dist;

	if (ray->side == 0)
		perp_dist = (ray->map_x - player.pos_x + (1 - ray->step_x) / 2)
			/ ray->dir_x;
	else
		perp_dist = (ray->map_y - player.pos_y + (1 - ray->step_y) / 2)
			/ ray->dir_y;
	wall.dist = perp_dist;
	wall.height = (int)(SCREEN_HEIGHT / wall.dist);
	wall.start = -wall.height / 2 + SCREEN_HEIGHT / 2;
	if (wall.start < 0)
		wall.start = 0;
	wall.end = wall.height / 2 + SCREEN_HEIGHT / 2;
	if (wall.end >= SCREEN_HEIGHT)
		wall.end = SCREEN_HEIGHT;
	return (wall);
}

static void	draw_wall(int x, int y, t_game *game, t_wall wall, t_tex tex)
{
	int	d;
	int	color;

	d = y * 256 - SCREEN_HEIGHT * 128 + wall.height * 128;
	tex.y = ((d * TEX_HEIGHT) / wall.height) / 256;
	color = get_tex_color(&game->texture.tex[tex.num], tex.x, tex.y);
	my_mlx_pixel_put(&game->img, x, y, color);
}

static void	draw_line(int x, t_ray ray, t_game *game, t_wall wall)
{
	t_tex	tex;
	int		y;
	double	walle;

	y = -1;
	while (++y < wall.start)
		my_mlx_pixel_put(&game->img, x, y, game->ceiling.hex);
	tex.num = get_texture_num(&ray);
	if (ray.side == 0)
		walle = game->player.pos_y + wall.dist * ray.dir_y;
	else
		walle = game->player.pos_x + wall.dist * ray.dir_x;
	walle -= floor(walle);
	tex.x = (int)(walle * TEX_WIDTH);
	if ((ray.side == 0 && ray.dir_x > 0) || (ray.side == 1 && ray.dir_y < 0))
		tex.x = TEX_WIDTH - tex.x - 1;
	y = wall.start - 1;
	while (++y <= wall.end)
		draw_wall(x, y, game, wall, tex);
	y -= 1;
	while (y < SCREEN_HEIGHT)
		my_mlx_pixel_put(&game->img, x, y++, game->floor.hex);
}

void	raycasting(t_game *game)
{
	t_ray	ray;
	t_wall	wall;
	int		x;

	x = -1;
	while (++x < SCREEN_WIDTH)
	{
		ray = init_ray(x, game->player);
		perform_dda(&ray, game);
		wall = init_wall(&ray, game->player);
		draw_line(x, ray, game, wall);
	}
}
