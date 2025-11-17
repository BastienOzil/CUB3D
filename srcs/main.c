/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:49:08 by bozil             #+#    #+#             */
/*   Updated: 2025/11/17 14:52:54 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Le t_game pourra etre remplacer
    juste c'est pour que j'apprenne
    pour l'instant :D */

#include "../includes/cub3d.h"

int main(int ac, char **av)
{
    t_game game;
    
    if (ac != 2 || !av[1])
    {
        printf("Usage: ./cub3D maps/map_name.cub\n");
        return (1);
    }
    if (!parse_map(av[1], &game.map))
    {
        printf("Error:\nInvalid map\n");
        return (1);
    }
    if (!is_map_possible(&game))
    {
        printf("Error:\nThe map is impossible to complete.\n");
        free(&game.map);
        exit(1);
    }
    game.moves = 0;
    game.player_x = 0;
    game.player_y = 0;
    start_game(&game);
    exit_game(&game);
    return (0);
}