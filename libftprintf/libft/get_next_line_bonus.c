/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 11:43:09 by alexfran          #+#    #+#             */
/*   Updated: 2026/02/10 14:44:32 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*empty_stash(char *stash)
{
	char	*temp;
	int		i;
	int		j;

	i = ((j = 0));
	if (!stash[i])
		return ((stash = free_stash(stash)));
	while (stash[i] != '\n' && stash[i])
		i++;
	if (!stash[i])
		return (stash = free_stash(stash));
	temp = malloc(ft_strlen(stash) - i + 1);
	if (!temp)
		return (NULL);
	i++;
	while (stash[i])
		temp[j++] = stash[i++];
	temp[j] = '\0';
	free(stash);
	stash = NULL;
	return (temp);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

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

char	*fill_stash(char *buf, int fd)
{
	static char	*stash[1024];
	char		*temp;
	char		*ret_line;
	int			ret;

	if (!stash[fd])
		stash[fd] = test_stash();
	ret = 1;
	while (ret && !ft_strchr(stash[fd], '\n'))
	{
		ret = read (fd, buf, BUFFER_SIZE);
		if (ret == -1)
		{
			stash[fd] = free_stash(stash[fd]);
			return (NULL);
		}
		buf[ret] = '\0';
		temp = ft_strjoin(stash[fd], buf);
		stash[fd] = free_stash(stash[fd]);
		stash[fd] = temp;
	}
	ret_line = read_line(stash[fd]);
	stash[fd] = empty_stash(stash[fd]);
	return (ret_line);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	line = fill_stash(buf, fd);
	if (!line)
	{
		free (buf);
		return (NULL);
	}
	free (buf);
	return (line);
}
