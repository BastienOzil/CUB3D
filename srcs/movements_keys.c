/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_keys.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:21:10 by bozil             #+#    #+#             */
/*   Updated: 2025/12/01 10:21:20 by bozil            ###   ########.fr       */
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
    else if (keycode == KEY_A)
        keycode = KEY_LEFT;
    else if (keycode == KEY_D)
        keycode = KEY_RIGHT;
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
    else if (keycode == KEY_A)
        keycode = KEY_LEFT;
    else if (keycode == KEY_D)
        keycode = KEY_RIGHT;
    if (keycode >= 0 && keycode < 70000)
        game->keys[keycode] = 0;
    return (0);
}
