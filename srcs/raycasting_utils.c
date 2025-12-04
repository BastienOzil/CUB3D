/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:10:00 by bozil             #+#    #+#             */
/*   Updated: 2025/12/04 11:40:31 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_ray side(t_ray ray, t_player player)
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

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_tex_color(t_img *texture, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	pixel = texture->addr + (y * texture->line_length + x
			* (texture->bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

int	get_texture_num(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->step_x < 0)
			return (3);
		else
			return (2);
	}
	else
	{
		if (ray->step_y < 0)
			return (0);
		else
			return (1);
	}
	return (0);
}
