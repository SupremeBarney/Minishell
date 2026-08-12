/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:41:29 by alexfran          #+#    #+#             */
/*   Updated: 2026/08/12 14:35:23 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_expansion(char *str, t_shell shell)
{
	int		i;
	int		flag;
	char	*res;
	char	*tmp_dollar;
	char	tmp[2];

	i = ((flag = 0));
	res = ft_strdup("");
	tmp[1] = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			tmp_dollar = handle_dollar(str, &i, shell, flag);
			res = strjoin_free(res, tmp_dollar);
			free(tmp_dollar);
		}
		else
		{
			tmp[0] = str[i++];
			res = strjoin_free(res, tmp);
		}
	}
	return (res);
}
