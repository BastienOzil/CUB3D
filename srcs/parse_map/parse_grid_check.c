/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_grid_check.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:03:51 by bozil             #+#    #+#             */
/*   Updated: 2025/12/08 14:16:39 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Vérifier s'il y a du contenu de map après une ligne vide.
 */

#include "../includes/cub3d.h"

int	check_no_map_after_empty(char **lines, int start, int height)
{
	int	i;

	i = start + height + 1;
	while (lines[i])
	{
		if (!is_empty_line(lines[i]))
		{
			if (ft_strchr(lines[i], '0') || ft_strchr(lines[i], '1'))
				return (0);
		}
		i++;
	}
	return (1);
}
