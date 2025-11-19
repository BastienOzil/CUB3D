/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 10:49:08 by bozil             #+#    #+#             */
/*   Updated: 2025/11/19 19:07:14 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	main(int ac, char **av)
{
	t_game game;

	if (ac != 2)
		return (ft_error("Usage: ./cub3D <map.cub>"));
	init_game(&game);
	if (!parse_file(av[1], &game))
	{
		free_game(&game);
		return (ft_error("Error\nInvalid map file"));
	}
	if (!check_map(&game))
	{
		free_game(&game);
		return (ft_error("Error\nInvalid map"));
	}
	init_player(&game);
	if (!start_game(&game))
	{
		free_game(&game);
		return (ft_error("Error\nFailed to start game"));
	}
	free_game(&game);
	return (0);
}