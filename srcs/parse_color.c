/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 23:34:13 by bozil             #+#    #+#             */
/*   Updated: 2025/11/24 13:40:27 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Parse les couleurs F/C: extrait les valeurs RGB, valide (0-255), 
 * convertit en hexa et stocke dans game.
 */

#include "../includes/cub3d.h"

static int	parse_rgb_values(char **rgb_split, int *r, int *g, int *b)
{
	char	*trimmed;

	trimmed = ft_strtrim(rgb_split[0], " \t\n");
	*r = ft_atoi(trimmed);
	free(trimmed);
	trimmed = ft_strtrim(rgb_split[1], " \t\n");
	*g = ft_atoi(trimmed);
	free(trimmed);
	trimmed = ft_strtrim(rgb_split[2], " \t\n");
	*b = ft_atoi(trimmed);
	free(trimmed);
	if (!validate_rgb_range(*r, *g, *b))
		return (0);
	return (1);
}

int	parse_color_line(char *line, t_game *game)
{
	int		i;
	int		type;
	char	**rgb_split;
	int		rgb[3];

	i = 0;
	type = get_color_type(line, &i);
	if (type == -1 || check_color_duplicate(game, type))
		return (1);
	i++;
	while (is_space(line[i]))
		i++;
	rgb_split = split_rgb_values(&line[i]);
	if (!rgb_split)
		return (1);
	if (!parse_rgb_values(rgb_split, &rgb[0], &rgb[1], &rgb[2]))
	{
		free_split(rgb_split);
		return (1);
	}
	free_split(rgb_split);
	store_color(game, type, rgb[0], rgb[1], rgb[2]);
	return (0);
}
