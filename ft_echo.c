/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:16:10 by nipichon          #+#    #+#             */
/*   Updated: 2026/07/31 17:03:24 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_count_words(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == ' ')
			i++;
		while (str[i] && str[i] != ' ')
		{
			write(1, &str[i], 1);
			i++;
		}
		while (str[i] && str[i] == ' ')
			i++;
		if (str[i])
			write(1, " ", 1);
	}
}

static int		ft_check_if_n(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (0);
	while (str[i])
	{
		if(str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo_n(char **args)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	if (!args || !args[0])
	{
		write(1, "\n", 1);
		return ;
	}
	i = 2;
	while (args[i])
	{
		if (count == 1 || ft_check_if_n(args[i]) != 1)
		{
			count = 1;
			j = 0;
			while(args[i][j])
			{
				if (args[i][j] != '\\')
					write (1, &args[i][j], 1);
				j++;
			}
			if (args[i + 1])
				write(1, " ", 1);
		}
		i++;
	}
	return ;
}

void	ft_echo(char **args)
{
	int	i;

	if (args[1] && ft_check_if_n(args[1]) == 1)
	{
		ft_echo_n(args);
		return ;
	}
	if (!args || !args[0])
	{
		write(1, "\n", 1);
		return ;
	}
	i = 1;
	while (args[i])
	{
		ft_count_words(args[i]);
		i++;
	}
	write(1, "\n", 1);
	return ;
}
