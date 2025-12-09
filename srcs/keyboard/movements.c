/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:01:23 by mpoirier          #+#    #+#             */
/*   Updated: 2025/12/09 14:24:10 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static bool	is_valid_position(t_game *game, double x, double y)
{
	double	margin;
	int		checks[4][2];
	int		i;

	margin = 0.1;
	checks[0][0] = (int)(x - margin);
	checks[0][1] = (int)(y - margin);
	checks[1][0] = (int)(x + margin);
	checks[1][1] = (int)(y - margin);
	checks[2][0] = (int)(x - margin);
	checks[2][1] = (int)(y + margin);
	checks[3][0] = (int)(x + margin);
	checks[3][1] = (int)(y + margin);
	if (x < margin || x >= (double)game->map.width - margin || y < margin
		|| y >= (double)game->map.height - margin)
		return (false);
	i = -1;
	while (++i < 4)
	{
		if (checks[i][0] < 0 || checks[i][0] >= game->map.width
			|| checks[i][1] < 0 || checks[i][1] >= game->map.height
			|| is_wall(game->map.grid[checks[i][1]][checks[i][0]]))
			return (false);
	}
	return (true);
}

static void	move_player(t_game *game, double a)
{
	char	**grid;
	double	new_x;
	double	new_y;

	grid = game->map.grid;
	new_x = game->player.pos_x + a * MOVE_SPEED * game->player.dir_x;
	new_y = game->player.pos_y + a * MOVE_SPEED * game->player.dir_y;
	if (is_valid_position(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_position(game, game->player.pos_x, new_y))
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
	game->player.dir_x = old_dir_x * cos(angle) - game->player.dir_y
		* sin(angle);
	game->player.dir_y = old_dir_x * sin(angle) + game->player.dir_y
		* cos(angle);
	game->player.plane_x = old_plane_x * cos(angle) - game->player.plane_y
		* sin(angle);
	game->player.plane_y = old_plane_x * sin(angle) + game->player.plane_y
		* cos(angle);
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
	if (is_valid_position(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_valid_position(game, game->player.pos_x, new_y))
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
