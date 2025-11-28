/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:17:28 by bozil             #+#    #+#             */
/*   Updated: 2025/11/28 14:42:32 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Initialise MLX, crée la fenêtre 1280x720, charge les textures
 * et lance la boucle du jeu (écran noir pour l'instant).
 */

#include "../includes/cub3d.h"

static int	close_game(t_game *game)
{
	(void)game;
	exit(0);
	return (0);
}

static int	init_mlx(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	if (!game->win)
		return (0);
	game->img.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->img.img)
		return (0);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	if (!game->img.addr)
		return (0);
	return (1);
}

int	render_frame(t_game *game)
{
	ft_memset(game->img.addr, 0, SCREEN_HEIGHT * (game->img.line_length));
	raycasting(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}

int	start_game(t_game *game)
{
	if (!init_mlx(game))
		return (0);
	if (!load_textures(game))
		return (0);
	mlx_hook(game->win, 17, 0, close_game, game);
	mlx_key_hook(game->win, handle_keypress, game);
	mlx_hook(game->win, 6, 1L << 6, handle_mouse, game);
	mlx_loop_hook(game->mlx, render_frame, game);
	ft_printf("Game initialized successfully!\n");
	ft_printf("Player at (%.2f, %.2f) facing (%.2f, %.2f)\n",
		game->player.pos_x, game->player.pos_y, game->player.dir_x,
		game->player.dir_y);
	mlx_loop(game->mlx);
	return (1);
}
