/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:44:40 by nipichon          #+#    #+#             */
/*   Updated: 2026/08/12 15:23:17 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd_curdir(t_env *pwd, int *exit_status)
{
	if (!pwd)
	{
		printf("cd: error retrieving current directory: ");
		printf("getcwd: cannot access parent directories: ");
		printf("No such file or directory\n");
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
}

void	ft_cd_backtrack(char *str, t_env *pwd, t_env *home, int *exit_status)
{
	char	*new_pwd;
	int		i;

	new_pwd = ft_strdup(pwd->value);
	i = ft_strlen(new_pwd) - 1;
	while (i > 0 && new_pwd[i] != '/')
		i--;
	new_pwd[i] = '\0';
	if (chdir(new_pwd) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", str);
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

char	*ft_squeeze_slashes(char *str)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(ft_strlen(str) + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		res[j++] = str[i];
		if (str[i] == '/')
			while (str[i] == '/')
				i++;
		else
			i++;
	}
	if (j > 1 && res[j - 1] == '/')
		j--;
	res[j] = '\0';
	return (res);
}
