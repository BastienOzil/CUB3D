/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 11:10:48 by marvin            #+#    #+#             */
/*   Updated: 2024/11/21 11:10:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
