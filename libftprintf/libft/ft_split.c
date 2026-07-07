/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 17:05:29 by alexfran          #+#    #+#             */
/*   Updated: 2025/12/02 12:58:27 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_c(const char *s, char c)
{
	int	i;
	int	count;
	int	flag;

	count = ((i = 0));
	flag = 0;
	while (s[i])
	{
		if (s[i] != c && flag == 0)
		{
			count++;
			flag = 1;
		}
		if (s[i] == c)
			flag = 0;
		i++;
	}
	return (count);
}

static void	*ft_free(char **res, int k)
{
	int	i;

	i = 0;
	if (!res)
		return (NULL);
	while (i < k)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

static char	*alloc_word(const char *s, int start, char c)
{
	char	*word;
	int		i;
	int		len;

	len = 0;
	while (s[start + len] != c && s[start + len])
		len++;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[start + i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	res = malloc (sizeof(char *) * (count_c(s, c) + 1));
	if (!res)
		return (NULL);
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
		{
			res[j] = alloc_word(s, i, c);
			if (!res[j])
				return (ft_free(res, j));
			j++;
		}
		i++;
	}
	res[j] = NULL;
	return (res);
}
