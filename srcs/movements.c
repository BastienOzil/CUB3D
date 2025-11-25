/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:01:23 by mpoirier          #+#    #+#             */
/*   Updated: 2025/11/25 15:01:19 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int is_wall(char c)
{
    return (c == '1' || c == ' ');
}

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
        ;
    else if (!is_wall(grid[(int)y][(int)(x + (a * MOVE_SPEED * sin(dir_x)))]))
        x += (a * MOVE_SPEED * sin(dir_x));
    if (y >= (double)(game->map.height) || y <= 0.00)
        ;
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
    return (0);
}