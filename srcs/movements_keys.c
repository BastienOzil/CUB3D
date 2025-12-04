/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_keys.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:21:10 by bozil             #+#    #+#             */
/*   Updated: 2025/12/04 10:59:55 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Gestion des événements clavier (keypress/keyrelease).
 */

#include "../includes/cub3d.h"

int handle_keypress(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
    {
        free_game(game);
        exit(0);
    }
    if (keycode == KEY_W)
        keycode = KEY_UP;
    else if (keycode == KEY_S)
        keycode = KEY_DOWN;
    else if (keycode == KEY_ALT)
        mlx_mouse_show(game->mlx, game->win);
    if (keycode >= 0 && keycode < 70000)
        game->keys[keycode] = 1;
    return (0);
}

int handle_keyrelease(int keycode, t_game *game)
{
    if (keycode == KEY_W)
        keycode = KEY_UP;
    else if (keycode == KEY_S)
        keycode = KEY_DOWN;
    else if (keycode == KEY_ALT)
    {
        mlx_mouse_hide(game->mlx, game->win);
        mlx_mouse_move(game->mlx, game->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    }
    if (keycode >= 0 && keycode < 70000)
        game->keys[keycode] = 0;
    return (0);
}
