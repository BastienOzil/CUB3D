/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:53:46 by bozil             #+#    #+#             */
/*   Updated: 2024/11/14 11:08:02 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d == s)
		return (dest);
	if (d < s)
	{
		while (n--)
		{
			*d = *s ;
			d++;
			s++;
		}
		return (dest);
	}
	else
	{
		d += n;
		s += n;
		while (n--)
			*(--d) = *(--s);
		return (dest);
	}
}
