/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:41:29 by alexfran          #+#    #+#             */
/*   Updated: 2026/08/22 16:31:58 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_pipe_all(int fd)
{
	char	buf[1024];
	char	*res;
	int		n;

	res = ft_strdup("");
	n = read(fd, buf, 1023);
	while (n > 0)
	{
		buf[n] = 0;
		res = strjoin_free(res, buf);
		n = read(fd, buf, 1023);
	}
	return (res);
}
