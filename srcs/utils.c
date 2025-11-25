/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpoirier <mpoirier@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 20:40:55 by bozil             #+#    #+#             */
/*   Updated: 2025/11/25 15:16:06 by mpoirier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Ce fichier contient des fonctions helper utilisées partout:
 * - is_space(): Vérifie si un caractère est un espace blanc (' ', '\t', '\n')
 * - free_split(): Libère un tableau de chaînes (résultat de ft_split)
 * - ft_strtrim_whitespace(): Enlève les espaces au début et à la fin
 */

#include "../includes/cub3d.h"

int is_wall(char c)
{
    return (c == '1' || c == ' ');
}

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	*ft_strtrim_whitespace(char *str)
{
	return (ft_strtrim(str, " \t\n\r"));
}
