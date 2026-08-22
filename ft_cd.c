/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:44:40 by nipichon          #+#    #+#             */
/*   Updated: 2026/08/22 16:05:50 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_cd_find_vars(t_env *env, t_env **pwd, t_env **home,
		t_env **old_pwd)
{
	*pwd = NULL;
	*home = NULL;
	*old_pwd = NULL;
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

static void	ft_cd_ensure_vars(t_env **first_env, t_env **pwd,
		t_env **old_pwd)
{
	char	*cwd;

	if (!*pwd)
	{
		cwd = getcwd(NULL, 0);
		*pwd = add_env_var(first_env, "PWD", cwd);
		free(cwd);
	}
	if (!*old_pwd)
		*old_pwd = add_env_var(first_env, "OLDPWD", NULL);
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
		cd_error(old_pwd->value, ": No such file or directory\n");
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

void	ft_cd(char *str, t_env **first_env, char **args, int *exit_status)
{
	t_env	*pwd;
	t_env	*home;
	t_env	*old_pwd;

	if (args[1] && args[2])
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
		*exit_status = 1;
		return ;
	}
	ft_cd_find_vars(*first_env, &pwd, &home, &old_pwd);
	ft_cd_ensure_vars(first_env, &pwd, &old_pwd);
	if (str && str[0] == '-' && str[1] == '\0')
	{
		ft_cd_previous(pwd, old_pwd, exit_status);
		return ;
	}
	ft_cd_set_oldpwd(old_pwd, pwd->value);
	ft_which_cd(str, pwd, home, exit_status);
}
