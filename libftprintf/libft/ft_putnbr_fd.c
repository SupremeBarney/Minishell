/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:24:03 by alexfran          #+#    #+#             */
/*   Updated: 2026/01/06 13:11:52 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	printn(char n, int fd)
{
	n += 48;
	write(fd, &n, 1);
}

void	ft_putnbr_fd(long n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else if (n <= 9 && n >= 0)
		printn(n, fd);
	else if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
		ft_putnbr_fd(n, fd);
	}
	else if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
}
