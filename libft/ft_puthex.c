/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:38:10 by bozil             #+#    #+#             */
/*   Updated: 2025/11/24 13:38:10 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"

int	ft_puthex(unsigned long n, int uppercase)
{
	int		c;
	char	*base;

	c = 0;
	base = "0123456789abcdef";
	if (uppercase)
		base = "0123456789ABCDEF";
	if (n >= 16)
		c += ft_puthex(n / 16, uppercase);
	ft_putchar(base[n % 16]);
	c += 1;
	return (c);
}
