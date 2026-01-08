/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:41:35 by bozil             #+#    #+#             */
/*   Updated: 2024/11/14 14:52:04 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*result;

	result = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			result = ((char *)&s[i]);
		i++;
	}
	if (c == '\0')
		return (((char *)&s[i]));
	return (result);
}
