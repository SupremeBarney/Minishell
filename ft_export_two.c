/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:30:06 by nipichon          #+#    #+#             */
/*   Updated: 2026/08/22 16:35:03 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_val_id_three(char *str, int i, int error)
{
	while (str[i] && str[i] != '=')
	{
		if (str[i] == '@' || str[i] == '-' || str[i] == '.' || str[i] == '}'
			|| str[i] == '{' || str[i] == '*' || str[i] == '#' || str[i] == '+')
			error++;
		if (str[i] == '!')
		{
			write (1, "bash: ", 6);
			while (str[i])
			{
				write (1, &str[i], 1);
				i++;
			}
			write (1, ": event not found\n", 18);
			return (0);
		}
		i++;
	}
	if (error >= 1)
	{
		printf("bash: export: '%s': not a valid identifier\n", str);
		return (0);
	}
	return (1);
}

static int	ft_val_id_two(char *str)
{
	int	i;
	int	error;

	error = 0;
	i = 0;
	if (str[0] == '-')
	{
		printf("bash: export: '-%c': invalid option\n", str[1]);
		return (0);
	}
	return (ft_val_id_three(str, i, error));
}

int	ft_is_valid_identifier(char *str)
{
	int	error;

	error = 0;
	if (str[0] == '\0')
	{
		printf("bash: export: `': not a valid identifier\n");
		return (0);
	}
	if (str[0] == '=')
		error++;
	if (str[0] == '%')
		error++;
	if (str[0] == '$' && str[1] == '?')
		error++;
	if (str[0] == '?')
		error++;
	if (str[0] >= '0' && str[0] <= '9')
		error++;
	if (error >= 1)
	{
		printf("bash: export: '%s': not a valid identifier\n", str);
		return (0);
	}
	return (ft_val_id_two(str));
}

int	ft_is_there_an_equal_or_not(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	if (str[i] == '=')
		return (1);
	return (0);
}

char	*before_equal(char *a)
{
	int		i;
	char	*ret;

	i = 0;
	while (a[i] && a[i] != '=')
		i++;
	ret = malloc(sizeof (char) * i + 1);
	i = 0;
	while (a[i] && a[i] != '=')
	{
		ret[i] = a[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
