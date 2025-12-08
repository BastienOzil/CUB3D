/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:03:27 by bozil             #+#    #+#             */
/*   Updated: 2025/12/08 14:16:32 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Validation et split des valeurs RGB.
 */

#include "../includes/cub3d.h"

static int	count_commas_and_check(char *rgb_str, int *comma_count)
{
	int	i;

	i = 0;
	*comma_count = 0;
	while (rgb_str[i] && is_space(rgb_str[i]))
		i++;
	if (rgb_str[i] == ',')
		return (0);
	while (rgb_str[i])
	{
		if (rgb_str[i] == ',')
		{
			(*comma_count)++;
			if (rgb_str[i + 1] == ',')
				return (0);
		}
		i++;
	}
	return (i);
}

static int	has_invalid_commas(char *rgb_str)
{
	int	i;
	int	comma_count;

	i = count_commas_and_check(rgb_str, &comma_count);
	if (i == 0)
		return (1);
	i--;
	while (i >= 0 && is_space(rgb_str[i]))
		i--;
	if (i >= 0 && rgb_str[i] == ',')
		return (1);
	if (comma_count != 2)
		return (1);
	return (0);
}

static int	validate_rgb_token(char *token)
{
	int	i;

	i = 0;
	while (token[i] && is_space(token[i]))
		i++;
	if (!token[i] || !ft_isdigit(token[i]))
		return (0);
	while (token[i] && ft_isdigit(token[i]))
		i++;
	while (token[i] && is_space(token[i]))
		i++;
	if (token[i] != '\0')
		return (0);
	return (1);
}

static int	validate_all_tokens(char **rgb_split)
{
	if (!validate_rgb_token(rgb_split[0]))
		return (0);
	if (!validate_rgb_token(rgb_split[1]))
		return (0);
	if (!validate_rgb_token(rgb_split[2]))
		return (0);
	return (1);
}

char	**split_rgb_values(char *rgb_str)
{
	char	**rgb_split;
	int		count;

	if (has_invalid_commas(rgb_str))
		return (NULL);
	rgb_split = ft_split(rgb_str, ',');
	if (!rgb_split)
		return (NULL);
	count = 0;
	while (rgb_split[count])
		count++;
	if (count != 3 || !validate_all_tokens(rgb_split))
	{
		free_split(rgb_split);
		return (NULL);
	}
	return (rgb_split);
}
