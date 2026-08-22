/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:44:40 by nipichon          #+#    #+#             */
/*   Updated: 2026/08/22 16:17:21 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_backtrack(char *str)
{
	return (str[0] == '.' && str[1] == '.'
		&& (str[2] == '\0' || str[2] == '/'));
}

void	ft_which_cd(char *str, t_env *pwd, t_env *home, int *exit_status)
{
	if (!str || str[0] == '\n')
	{
		ft_cd_with_nothing(home, pwd, exit_status);
		return ;
	}
	else if (ft_is_backtrack(str))
		ft_cd_backtrack(str, pwd, home, exit_status);
	else if (str[0] == '.' && str[1] == '\0')
		ft_cd_curdir(pwd, exit_status);
	else if (str[0] == '/')
		ft_cd_true_path(str, pwd, exit_status);
	else
		ft_cd_relative_path(str, pwd, exit_status);
}

void	ft_cd_curdir(t_env *pwd, int *exit_status)
{
	if (!pwd)
	{
		ft_putstr_fd("cd: error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		*exit_status = 1;
		return ;
	}
	if (chdir(pwd->value) == -1)
		*exit_status = 1;
	else
		*exit_status = 0;
}

static void	ft_cd_backtrack_rest(char *str, t_env *pwd, t_env *home,
		int *exit_status)
{
	char	*rep;
	int		i;

	i = 3;
	rep = malloc(ft_strlen(str) - 2);
	while (str[i])
	{
		rep[i - 3] = str[i];
		i++;
	}
	rep[i - 3] = '\0';
	str = ft_strdup(rep);
	free(rep);
	ft_which_cd(str, pwd, home, exit_status);
	free(str);
}

void	ft_cd_backtrack(char *str, t_env *pwd, t_env *home, int *exit_status)
{
	char	*new_pwd;
	int		i;

	new_pwd = ft_strdup(pwd->value);
	i = ft_strlen(new_pwd) - 1;
	while (i > 0 && new_pwd[i] != '/')
		i--;
	if (i == 0)
		new_pwd[i++] = '/';
	new_pwd[i] = '\0';
	if (chdir(new_pwd) == -1)
	{
		cd_error(str, ": No such file or directory\n");
		free(new_pwd);
		*exit_status = 1;
		return ;
	}
	free(pwd->value);
	pwd->value = new_pwd;
	*exit_status = 0;
	if (str[2] && str[2] == '/')
		ft_cd_backtrack_rest(str, pwd, home, exit_status);
}
