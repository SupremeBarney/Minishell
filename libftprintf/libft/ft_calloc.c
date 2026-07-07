/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 11:05:12 by alexfran          #+#    #+#             */
/*   Updated: 2025/12/01 17:24:04 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	void	*memory;
	size_t	i;

	i = 0;
	memory = malloc(elementCount * elementSize);
	if (!memory)
		return (NULL);
	while (i < elementCount * elementSize)
	{
		((char *)memory)[i] = '\0';
		i++;
	}
	return (memory);
}
