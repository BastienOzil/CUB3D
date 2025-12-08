/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:04:16 by bozil             #+#    #+#             */
/*   Updated: 2025/12/08 14:16:42 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Split qui conserve les lignes vides (contrairement à ft_split).
 * Nécessaire pour détecter les lignes vides dans la map.
 */

#include "../includes/cub3d.h"

static int	count_lines(char *content)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!content || !content[0])
		return (0);
	while (content[i])
	{
		if (content[i] == '\n')
			count++;
		i++;
	}
	if (i > 0 && content[i - 1] != '\n')
		count++;
	return (count);
}

static char	*extract_line(char *content, int *index)
{
	int		start;
	int		len;
	char	*line;

	start = *index;
	len = 0;
	while (content[*index] && content[*index] != '\n')
	{
		(*index)++;
		len++;
	}
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	ft_strlcpy(line, &content[start], len + 1);
	if (content[*index] == '\n')
		(*index)++;
	return (line);
}

char	**split_lines(char *content)
{
	char	**lines;
	int		line_count;
	int		i;
	int		index;

	line_count = count_lines(content);
	lines = (char **)malloc(sizeof(char *) * (line_count + 1));
	if (!lines)
		return (NULL);
	i = 0;
	index = 0;
	while (i < line_count)
	{
		lines[i] = extract_line(content, &index);
		if (!lines[i])
		{
			while (i > 0)
				free(lines[--i]);
			free(lines);
			return (NULL);
		}
		i++;
	}
	lines[i] = NULL;
	return (lines);
}
