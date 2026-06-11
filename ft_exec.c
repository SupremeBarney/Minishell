/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 10:09:28 by nipichon          #+#    #+#             */
/*   Updated: 2026/06/11 12:18:07 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(t_env *path, char *str, char **argv, t_env *first_env)
{
	if (!str)
		return ;
	if (path)
	{
		ft_exec_path(path, argv, first_env, str);
	}
	else if (str[0] == '/')
	{
		ft_exec_absolute(argv, first_env, str);
	}
	else
	{
		ft_exec_relative(argv, first_env, str);
	}
}

void	ft_exec_path(t_env *path, char **argv, t_env *env, char *str)
{
	char	**ret;
	int		i;

	if (!path || !path->value)
		return ;
	ret = ft_split(path->value, ':');
	i = 0;
	while (ret[i])
	{
		ret[i] = ft_strjoin(ret[i], '/');
		ret[i] = ft_strjoin(ret[i], str);
		if (access(ret[i], X_OK) == 0)
		{
			execve(ret[i], argv, env);
			while (ret[i])
				i++;
			ft_free_split(ret, i);
			return ;
		}
		i++;
	}
}

void	ft_free_split(char **split, int i)
{
	i--;
	while (i > 0)
	{
		free(split[i]);
		i--;
	}
	free(split);
}

void	ft_exec_absolute(char **argv, t_env *env, char *str)
{
	if (!str)
		return ;
	if (access(str, X_OK) == 0)
	{
		execve(str, argv, env);
		return ;
	}
}

void	ft_exec_relative(char **argv, t_env *env, char *str,)
{
	char	*ret;
	char	*first_half;
	int		i;
	t_env	*pwd;

	pwd = ft_find_pwd(env);
	i = 0;
	first_half = malloc (ft_strlen(pwd->value) + 2);
	if (!first_half)
		return ;
	while (pwd->value[i])
	{
		first_half[i] = pwd->value[i];
		i++;
	}
	first_half[i] = '/';
	first_half[i + 1] = '\0';
	ret = ft_strjoin(first_half, str);
	if (access(ret, X_OK) == 0)
	{
		execve(ret, argv, env);
		(free(first_half), free(ret));
		return ;
	}
	free(first_half);
}


