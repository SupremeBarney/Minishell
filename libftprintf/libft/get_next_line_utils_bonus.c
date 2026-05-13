/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 11:45:22 by alexfran          #+#    #+#             */
/*   Updated: 2026/02/10 14:39:26 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		l1;
	int		l2;
	int		i;
	int		j;

	i = ((j = ((l1 = ((l2 = 0))))));
	if (s1)
		l1 = ft_strlen(s1);
	if (s2)
		l2 = ft_strlen(s2);
	res = malloc(l1 + l2 + 1);
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

char	*read_line(char *stash)
{
	char	*line;
	int		i;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
	{
		line = ft_substr(stash, 0, i + 1);
		return (line);
	}
	return (ft_substr(stash, 0, i));
}

char	*test_stash(void)
{
	char	*stash;

	stash = malloc(1);
	if (!stash)
		return (NULL);
	stash[0] = '\0';
	return (stash);
}

char	*free_stash(char *stash)
{
	free (stash);
	stash = NULL;
	return (stash);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i++;
	}
	if (s[i] == '\0' && (char)c == '\0')
		return ((char *)s + i);
	return (NULL);
}
