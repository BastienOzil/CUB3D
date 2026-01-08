/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 11:48:45 by bozil             #+#    #+#             */
/*   Updated: 2025/11/24 13:38:47 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr(void *ptr)
{
	unsigned long	n;
	int				count;

	n = (unsigned long)ptr;
	if (n == 0)
		return (write(1, "(nil)", 5));
	count = 0;
	count += ft_putstr("0x");
	count += ft_puthex(n, 0);
	return (count);
}
