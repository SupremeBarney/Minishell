/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:44:40 by nipichon          #+#    #+#             */
/*   Updated: 2026/08/12 14:56:27 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd_true_path(char *str, t_env *pwd, int *exit_status)
{
	if (chdir(str) == -1)
	{
		ft_putstr_fd("bash: cd: ", 2);
		perror(str);
		*exit_status = 1;
	}
	else
	{
		free(pwd->value);
		pwd->value = ft_squeeze_slashes(str);
		*exit_status = 0;
	}
}

static char	*ft_cd_join_path(char *pwd_value, char *str)
{
	char	*first_half;
	char	*ret;
	int		i;

	i = 0;
	first_half = malloc(ft_strlen(pwd_value) + 2);
	while (pwd_value[i])
	{
		first_half[i] = pwd_value[i];
		i++;
	}
	first_half[i] = '/';
	first_half[i + 1] = '\0';
	ret = ft_strjoin(first_half, str);
	free(first_half);
	return (ret);
}

void	ft_cd_relative_path(char *str, t_env *pwd, int *exit_status)
{
	char	*ret;
	char	*clean;

	ret = ft_cd_join_path(pwd->value, str);
	if (chdir(ret) == -1)
	{
		ft_putstr_fd("bash: cd: ", 2);
		perror(str);
		free(ret);
		*exit_status = 1;
		return ;
	}
	clean = ft_squeeze_slashes(ret);
	free(ret);
	free(pwd->value);
	pwd->value = clean;
	*exit_status = 0;
}

void	ft_cd_with_nothing(t_env *home, t_env *pwd, int *exit_status)
{
	if (!home || !home->value || !home->value[0])
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		*exit_status = 1;
		return ;
	}
	if (chdir(home->value) == -1)
	{
		*exit_status = 1;
		return ;
	}
	free(pwd->value);
	pwd->value = ft_strdup(home->value);
	*exit_status = 0;
}
