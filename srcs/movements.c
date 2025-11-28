/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:01:23 by mpoirier          #+#    #+#             */
/*   Updated: 2025/11/28 14:21:37 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

/*
* Applique les deplacement du joueur sur la carte
* de la souris du POV du joueur et de sa rotation.
*/

static void move(t_game *game, double a)
{
    char    **grid;
    double  x;
    double  y;
    double  dir_x;
    double  dir_y;
    
    x = (game->player).plane_x;
    y = (game->player).plane_y;
    dir_x = (game->player).dir_x;
    dir_y = (game->player).dir_y;
    grid = (game->map).grid;
    if (x >= (double)(game->map.width) || x <= 0.00)
    {
        ;
    }
    else if (!is_wall(grid[(int)y][(int)(x + (a * MOVE_SPEED * sin(dir_x)))]))
        x += (a * MOVE_SPEED * sin(dir_x));
    if (y >= (double)(game->map.height) || y <= 0.00)
    {
        ;
    }
    if (!is_wall(grid[(int)(y + (a * MOVE_SPEED) * cos(dir_y))][(int)x]))
        y += (a * MOVE_SPEED * cos(dir_y));
    (game->player).plane_x = x;
    (game->player).plane_y = y;
}

static void rotate(t_game *game, double a)
{
    double dir_x;
    double dir_y;
    
    a =  (a * ROT_SPEED) * M_PI / 180.0;
    dir_x = (game->player).dir_x;
    dir_y = (game->player).dir_y;
    (game->player).dir_x = dir_x * cos(a) - dir_y * sin(a);
    (game->player).dir_y = dir_x * sin(a) + dir_y * cos(a);
}

static void strafe(t_game *game, double a)
{
    int nine;

    nine = (90.0 / ROT_SPEED);
    rotate(game, a * nine);
    move(game, +2.00);
    rotate(game, -a * nine);
}

int handle_keypress(int keycode, t_game *game)
{
    if (KEY_W  == keycode || KEY_UP == keycode)
        move(game, +1.00);
    if (KEY_S == keycode || KEY_DOWN == keycode)
        move(game, -1.00);
    if (KEY_A == keycode)
        strafe(game, +1.00);
    if (KEY_D == keycode)
        strafe(game, -1.00);
    if (KEY_LEFT == keycode)
        rotate(game, +1.00);
    if (KEY_RIGHT == keycode)
        rotate(game, -1.00);
    render_frame(game);
    return (0);
}

int handle_mouse(int mouse_x, int mouse_y, t_game *game)
{
    static int  last_x = -1;
    int         delta_x;
    
    (void)mouse_y;
    if (last_x == -1)
    {
        last_x = mouse_x;
        return (0);
    }
    delta_x = mouse_x - last_x;
    if (delta_x != 0)
        rotate(game, delta_x * 0.002);
    last_x = mouse_x;
    render_frame(game);
    return (0);
}

/* Si on veut s'amuser à cacher le curseur (type FPS)
int handle_mouse(int mouse_x, int mouse_y, t_game *game)
{
    int         delta_x;
    
    delta_x = mouse_x - (SCREEN_WIDTH / 2);
    if (abs(delta_x) < 2)
        rotate(game, delta_x * 0.002);
    mlx_mouse_move(game->mlx, game->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
    return (0);
}
et add to init_mlx:
    mlx_mouse_hide(game->mlx, game->win);
*/