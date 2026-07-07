/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 11:19:19 by alexfran          #+#    #+#             */
/*   Updated: 2025/12/01 16:55:59 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	temp;

	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)&big[0]);
	if (len == 0)
		return (NULL);
	while (big[i] && i < len)
	{
		j = 0;
		temp = i;
		while (big[temp] == little[j] && little[j] && temp < len)
		{
			temp++;
			j++;
		}
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
