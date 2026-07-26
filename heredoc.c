/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:41:29 by alexfran          #+#    #+#             */
/*   Updated: 2026/06/11 00:00:00 by alexfran         ###   ########.fr       */
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

char	*read_heredoc(char *delimiter, t_shell shell)
{
	char	*res;
	char	*tmp;
	char	*expanse;

	res = ft_strdup("");
	while (1)
	{
		tmp = readline("> ");
		if (!tmp)
			break ;
		if (g_signal == SIGINT)
			return (free(res), free(tmp), NULL);
		expanse = heredoc_expansion(tmp, shell);
		free(tmp);
		tmp = expanse;
		if (!ft_strncmp(delimiter, tmp, ft_strlen(delimiter) + 1))
		{
			free(tmp);
			break ;
		}
		res = strjoin_free(res, tmp);
		res = strjoin_free(res, "\n");
		free(tmp);
	}
	return (res);
}
