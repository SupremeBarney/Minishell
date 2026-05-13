/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 17:12:38 by alexfran          #+#    #+#             */
/*   Updated: 2025/12/02 10:43:01 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	if (start >= ft_strlen(s))
	{
		sub = malloc(1);
		if (!sub)
			return (NULL);
		sub[0] = '\0';
		return (sub);
	}
	if (len < ft_strlen(s) - start)
		sub = malloc(sizeof(char) * len + 1);
	else
		sub = malloc(sizeof(char) * (ft_strlen(s) - start) + 1);
	if (!sub)
		return (NULL);
	while (i < len && s[start])
	{
		sub[i++] = s[start];
		start++;
	}
	sub[i] = '\0';
	return (sub);
}
