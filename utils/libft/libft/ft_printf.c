/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bozil <bozil@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 11:08:19 by bozil             #+#    #+#             */
/*   Updated: 2024/11/23 11:47:42 by bozil            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	short_cut(char specifier, va_list args)
{
	int	c;

	c = 0;
	if (specifier == 'c')
		c += ft_putchar(va_arg(args, int));
	else if (specifier == 's')
		c += ft_putstr(va_arg(args, char *));
	else if (specifier == 'p')
		c += ft_putptr(va_arg(args, void *));
	else if (specifier == 'd' || specifier == 'i')
		c += ft_putnbr(va_arg(args, int));
	else if (specifier == 'u')
		c += ft_putnbr_unsigned(va_arg(args, unsigned int));
	else if (specifier == 'x')
		c += ft_puthex(va_arg(args, unsigned int), 0);
	else if (specifier == 'X')
		c += ft_puthex(va_arg(args, unsigned int), 1);
	else if (specifier == '%')
		c += ft_putchar('%');
	return (c);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i] != '\0')
	{
		if (format[i] == '%')
		{
			count += short_cut(format[i + 1], args);
			i++;
		}
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
