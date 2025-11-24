/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:22:19 by bozil             #+#    #+#             */
/*   Updated: 2025/11/24 13:40:20 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Affiche un message d'erreur sur stderr et retourne 1 (code d'erreur).
 */

#include "../includes/cub3d.h"

int	ft_error(char *message)
{
	ft_putendl_fd(message, 2);
	return (1);
}
