/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:44:50 by alexfran          #+#    #+#             */
/*   Updated: 2025/11/30 16:56:54 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	start(char const *s1, char const *set)
{
	int	start;
	int	is_set;
	int	i;

	start = 0;
	is_set = 1;
	while (s1[start] && is_set)
	{
		i = 0;
		is_set = 0;
		while (set[i])
		{
			if (s1[start] == set[i])
			{
				start++;
				is_set = 1;
			}
			i++;
		}
	}
	return (start);
}

static int	end(char const *s1, char const *set, int start)
{
	int	end;
	int	is_set;
	int	i;

	end = ft_strlen(s1) - 1;
	is_set = 1;
	while ((end > start) && is_set)
	{
		is_set = 0;
		i = 0;
		while (set[i])
		{
			if (s1[end] == set[i])
			{
				end--;
				is_set = 1;
			}
			i++;
		}
	}
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		i;
	int		starto;
	int		endo;

	i = 0;
	starto = start(s1, set);
	endo = end(s1, set, starto);
	res = malloc(sizeof(char) * (endo - starto + 1) + 1);
	if (!res)
		return (NULL);
	while (starto <= endo)
	{
		res[i] = s1[starto];
		i++;
		starto++;
	}
	res[i] = '\0';
	return (res);
}

// int main(void)
// {
// 	char s1[] = " lorem ipsum dolor sit amet";
// 	printf("%s\n", ft_strtrim(s1, "l "));
// }