/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements_keys.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 10:21:10 by bozil             #+#    #+#             */
/*   Updated: 2025/12/04 11:45:22 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Gestion des événements clavier (keypress/keyrelease)
 * et souris .
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

static int handle_alt_press(t_game *game, int *alt_was_pressed)
{
    if (!(*alt_was_pressed))
    {
        mlx_mouse_show(game->mlx, game->win);
        *alt_was_pressed = 1;
    }
    return (0);
}

static int handle_alt_release(t_game *game, int *alt_was_pressed,
                              int *last_mouse_x)
{
    mlx_mouse_hide(game->mlx, game->win);
    mlx_mouse_move(game->mlx, game->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    *last_mouse_x = SCREEN_WIDTH / 2;
    *alt_was_pressed = 0;
    return (0);
}

int handle_mouse(int mouse_x, int mouse_y, t_game *game)
{
    static int alt_was_pressed = 0;
    static int last_mouse_x = SCREEN_WIDTH / 2;
    int delta_x;

    (void)mouse_y;
    if (game->keys[KEY_ALT])
        return (handle_alt_press(game, &alt_was_pressed));
    if (alt_was_pressed)
        return (handle_alt_release(game, &alt_was_pressed, &last_mouse_x));
    if (abs(mouse_x - SCREEN_WIDTH / 2) < 5)
    {
        last_mouse_x = mouse_x;
        return (0);
    }
    delta_x = mouse_x - last_mouse_x;
    if (delta_x != 0)
    {
        rotate(game, delta_x * 0.5);
        last_mouse_x = SCREEN_WIDTH / 2;
        mlx_mouse_move(game->mlx, game->win, SCREEN_WIDTH / 2,
                       SCREEN_HEIGHT / 2);
    }
    return (0);
}
