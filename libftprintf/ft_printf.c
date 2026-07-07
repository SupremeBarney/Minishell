/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:38:08 by alexfran          #+#    #+#             */
/*   Updated: 2026/01/14 09:43:55 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "ft_printf.h"
#include <stdarg.h>

int	conversion_x(va_list args, int y)
{
	int				count;
	int				p;
	unsigned int	x;

	count = 0;
	p = va_arg(args, int);
	x = p;
	if (x == 0)
		count++;
	if (x == 16)
		count = 2;
	while (x != 0 && x != 16)
	{
		x /= 16;
		count++;
	}
	ft_putnbr_hexa(p, y);
	return (count);
}

int	conversion_u(va_list args)
{
	unsigned int	n;
	int				count;

	n = va_arg(args, unsigned int);
	count = 0;
	if (n == 0)
		count = 1;
	else
	{
		unsigned int tmp = n;
		while (tmp > 0)
		{
			tmp /= 10;
			count++;
		}
	}
	ft_putnbr_fd(n, 1);
	return (count);
}

static int	condition(char c, va_list va)
{
	if (c == 'c')
		return (conversion_c(va));
	else if (c == 's')
		return (conversion_s(va));
	else if (c == 'p')
		return (conversion_p(va));
	else if (c == 'd' || c == 'i')
		return (conversion_d(va));
	else if (c == 'u')
		return (conversion_u(va));
	else if (c == 'x')
		return (conversion_x(va, 0));
	else if (c == 'X')
		return (conversion_x(va, 1));
	else if (c == '%')
	{
		ft_putchar_fd('%', 1);
		return (1);
	}
	else
	{
		(ft_putchar_fd('%', 1), ft_putchar_fd(c, 1));
		return (2);
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	va_list	va;
	int		i;
	int		res;

	va_start(va, format);
	i = ((res = 0));
	if (!format)
		return (0);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{	
			res += condition(format[i + 1], va);
			i += 2;
			res -= 2;
		}
		else
			ft_putchar_fd(format[i++], 1);
	}
	res += i;
	va_end(va);
	return (res);
}
