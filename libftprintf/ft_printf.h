/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 12:53:48 by alexfran          #+#    #+#             */
/*   Updated: 2025/12/09 15:43:19 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft/libft.h"

int		ft_printf(const char *format, ...);
int		conversion_c(va_list args);
int		conversion_s(va_list args);
int		conversion_p(va_list args);
int		conversion_d(va_list args);
int		conversion_u(va_list args);
int		conversion_x(va_list args, int y);
void	ft_putnbr_hexa(unsigned long n, int x);

#endif
