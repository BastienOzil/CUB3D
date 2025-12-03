/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:01:23 by mpoirier          #+#    #+#             */
/*   Updated: 2025/12/03 08:55:03 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
 * Applique les deplacement du joueur sur la carte
 * de la souris du POV du joueur et de sa rotation.
 */

static void	move_player(t_game *game, double a)
{
	char	**grid;
	double	new_x;
	double	new_y;

	grid = game->map.grid;
	new_x = game->player.pos_x + a * MOVE_SPEED * game->player.dir_x;
	new_y = game->player.pos_y + a * MOVE_SPEED * game->player.dir_y;
	if (new_x > 0.00 && new_x < (double)(game->map.width))
		if (!is_wall(grid[(int)game->player.pos_y][(int)new_x]))
			game->player.pos_x = new_x;
	if (new_y > 0.00 && new_y < (double)(game->map.height))
		if (!is_wall(grid[(int)new_y][(int)game->player.pos_x]))
			game->player.pos_y = new_y;
}

void	rotate(t_game *game, double a)
{
	double	old_dir_x;
	double	old_plane_x;
	double	angle;

	angle = (a * ROT_SPEED) * M_PI / 180.0;
	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = old_dir_x * cos(angle) - game->player.dir_y * sin(angle);
	game->player.dir_y = old_dir_x * sin(angle) + game->player.dir_y * cos(angle);
	game->player.plane_x = old_plane_x * cos(angle) - game->player.plane_y * sin(angle);
	game->player.plane_y = old_plane_x * sin(angle) + game->player.plane_y * cos(angle);
}

static void	strafe_player(t_game *game, double a)
{
	char	**grid;
	double	new_x;
	double	new_y;
	double	perp_x;
	double	perp_y;

	grid = game->map.grid;
	perp_x = -game->player.dir_y;
	perp_y = game->player.dir_x;
	new_x = game->player.pos_x + a * MOVE_SPEED * perp_x;
	new_y = game->player.pos_y + a * MOVE_SPEED * perp_y;
	if (new_x > 0.00 && new_x < (double)(game->map.width))
		if (!is_wall(grid[(int)game->player.pos_y][(int)new_x]))
			game->player.pos_x = new_x;
	if (new_y > 0.00 && new_y < (double)(game->map.height))
		if (!is_wall(grid[(int)new_y][(int)game->player.pos_x]))
			game->player.pos_y = new_y;
}

void	process_movement(t_game *game)
{
	if (game->keys[KEY_UP])
		move_player(game, +1.00);
	if (game->keys[KEY_DOWN])
		move_player(game, -1.00);
	if (game->keys[KEY_LEFT])
		rotate(game, -1.00);
	if (game->keys[KEY_RIGHT])
		rotate(game, +1.00);
	if (game->keys[KEY_A])
		strafe_player(game, -1.00);
	if (game->keys[KEY_D])
		strafe_player(game, +1.00);
}

int	handle_mouse(int mouse_x, int mouse_y, t_game *game)
{
	static int	last_x = SCREEN_WIDTH / 2;
	int			delta_x;

	(void)mouse_y;
	delta_x = mouse_x - last_x;
	if (delta_x != 0)
	{
		rotate(game, delta_x * 0.01);
		last_x = SCREEN_WIDTH / 2;
		mlx_mouse_move(game->mlx, game->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}
	return (0);
}
