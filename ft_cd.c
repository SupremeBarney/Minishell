/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:44:40 by nipichon          #+#    #+#             */
/*   Updated: 2026/08/12 14:58:16 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cd_find_vars(t_env *env, t_env **pwd, t_env **home,
		t_env **old_pwd)
{
	while (env)
	{
		if (ft_strncmp("PWD", env->name, 4) == 0)
			*pwd = env;
		if (ft_strncmp("HOME", env->name, 5) == 0)
			*home = env;
		if (ft_strncmp("OLDPWD", env->name, 7) == 0)
			*old_pwd = env;
		env = env->next;
	}
}

static void	ft_cd_previous(t_env *pwd, t_env *old_pwd, int *exit_status)
{
	char	*tmp;

	if (!old_pwd || !old_pwd->value)
	{
		ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
		*exit_status = 1;
		return ;
	}
	if (chdir(old_pwd->value) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", old_pwd->value);
		*exit_status = 1;
		return ;
	}
	tmp = pwd->value;
	pwd->value = ft_strdup(old_pwd->value);
	free(old_pwd->value);
	old_pwd->value = tmp;
	printf("%s\n", pwd->value);
	*exit_status = 0;
}

void	set_everything_to_null(t_env **pwd, t_env **home, t_env **old_pwd)
{
	*pwd = NULL;
	*home = NULL;
	*old_pwd = NULL;
}

void	ft_cd(char *str, t_env *first_env, char **args, int *exit_status)
{
	t_env	*pwd;
	t_env	*home;
	t_env	*old_pwd;

	if (!first_env)
	{
		ft_which_cd(str, NULL, NULL, exit_status);
		return ;
	}
	if (args[1] && args[2])
	{
		printf ("bash: cd: too many arguments\n");
		*exit_status = 1;
		return ;
	}
	set_everything_to_null(&pwd, &home, &old_pwd);
	ft_cd_find_vars(first_env, &pwd, &home, &old_pwd);
	if (str && str[0] == '-' && str[1] == '\0')
	{
		ft_cd_previous(pwd, old_pwd, exit_status);
		return ;
	}
	old_pwd->value = ft_strdup(pwd->value);
	ft_which_cd(str, pwd, home, exit_status);
}

void	ft_which_cd(char *str, t_env *pwd, t_env *home, int *exit_status)
{
	if (!str || str[0] == '\n')
	{
		ft_cd_with_nothing(home, pwd, exit_status);
		return ;
	}
	else if (str[0] == '.')
	{
		if (str[1] == '.')
		{
			if (str[2] == '\0' || str[2] == '/')
				ft_cd_backtrack(str, pwd, home, exit_status);
		}
		if (str[1] == '\0')
		{
			ft_cd_curdir(pwd, exit_status);
			return ;
		}
	}
	else if (str[0] == '/')
		ft_cd_true_path(str, pwd, exit_status);
	else
		ft_cd_relative_path(str, pwd, exit_status);
}
