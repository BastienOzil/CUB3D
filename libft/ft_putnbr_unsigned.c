/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 13:38:20 by bozil             #+#    #+#             */
/*   Updated: 2025/11/24 13:38:44 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_unsigned(unsigned int n)
{
	int	c;

	c = 0;
	if (n >= 10)
		c += ft_putnbr_unsigned(n / 10);
	ft_putchar(n % 10 + '0');
	c++;
	return (c);
}
