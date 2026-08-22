/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outils.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:54:58 by alexfran          #+#    #+#             */
/*   Updated: 2026/08/12 13:57:26 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_hexa(unsigned long n, int x)
{
	char	*base_maj;
	char	*base_min;

	base_maj = "0123456789ABCDEF";
	base_min = "0123456789abcdef";
	if (n < 16)
	{
		if (x)
			ft_putchar_fd(base_maj[n], 1);
		else
			ft_putchar_fd(base_min[n], 1);
	}
	else
	{
		ft_putnbr_hexa(n / 16, x);
		ft_putnbr_hexa(n % 16, x);
	}
}

int	conversion_c(va_list args)
{
	char	c;

	c = (char)va_arg(args, int);
	ft_putchar_fd(c, 1);
	return (1);
}

int	conversion_s(va_list args)
{
	int		i;
	char	*c;

	i = 0;
	c = va_arg(args, char *);
	if (!c)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	while (c[i])
		ft_putchar_fd(c[i++], 1);
	return (i);
}

int	conversion_p(va_list args)
{
	unsigned int	count;
	unsigned long	p;
	unsigned long	x;

	count = 0;
	p = (unsigned long)va_arg(args, void *);
	x = p;
	if (x == (unsigned long) NULL)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	if (x == 0)
		count = 1;
	while (x != 0)
	{
		x /= 16;
		count++;
	}
	ft_putstr_fd("0x", 1);
	ft_putnbr_hexa(p, 0);
	return (count + 2);
}

int	conversion_d(va_list args)
{
	int	d;
	int	x;
	int	count;

	count = 0;
	d = va_arg(args, int);
	x = d;
	if (x == 0)
		count = 1;
	if (x < 0)
		count += 1;
	while (x != 0)
	{
		x /= 10;
		count++;
	}
	ft_putnbr_fd(d, 1);
	return (count);
}
