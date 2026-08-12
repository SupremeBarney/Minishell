/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:41:29 by alexfran          #+#    #+#             */
/*   Updated: 2026/08/12 14:23:45 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	slash_parser(char *read_line)
{
	struct stat	st;
	char		*cmd;
	int			len;

	if (read_line[0] != '/')
		return (0);
	len = 0;
	while (read_line[len] && read_line[len] != ' ')
		len++;
	cmd = ft_substr(read_line, 0, len);
	if (!cmd)
		return (0);
	if (stat(cmd, &st) == 0 && S_ISDIR(st.st_mode))
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		free(cmd);
		return (1);
	}
	free(cmd);
	return (0);
}

int	pipe_with_space(char *read_line)
{
	if (read_line[0] == '|' && read_line[1] == ' ')
	{
		ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
		return (1);
	}
	return (0);
}

int	ampersand_parser(char *read_line)
{
	if (read_line[0] == '&')
	{
		if (read_line[1] == '&')
		{
			ft_putstr_fd("bash: syntax error near unexpected token `&&'\n", 2);
			return (1);
		}
		ft_putstr_fd("bash: syntax error near unexpected token `&'\n", 2);
		return (1);
	}
	return (0);
}

int	quote_state(char *str)
{
	int	i;
	int	quote_flag;

	i = 0;
	quote_flag = 0;
	while (str[i])
	{
		if (str[i] == '\'' && quote_flag != 2)
			quote_flag = 1 - quote_flag;
		else if (str[i] == '"' && quote_flag != 1)
			quote_flag = 2 - quote_flag;
		i++;
	}
	return (quote_flag);
}

void	quotes_error(char *tmp, int state)
{
	if (!tmp && state == 1)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd("unexpected EOF while looking for matching `''\n", 2);
	}
	if (!tmp && state == 2)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd("unexpected EOF while looking for matching `\"'\n", 2);
	}
}
