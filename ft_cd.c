/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:44:40 by nipichon          #+#    #+#             */
/*   Updated: 2026/08/09 13:55:48 by marvin           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "minishell.h"

// pour tout les fonctions il faudra rajouter un moyen d'avoir tout les variable d'environement

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
	pwd = NULL;
	home = NULL;
	old_pwd = NULL;
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
			if (str[2] == '\0' || str[2] =='/')
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

void	ft_cd_true_path(char *str, t_env *pwd, int *exit_status)
{
	if (chdir(str) == -1)
	{
		printf("cd: %s: No such file or directory\n", str); //faudra que je fasse une fonction pour return la bonne erreur plus tard
		*exit_status = 1;
	}
	else
	{
		free(pwd->value);
		pwd->value = ft_strdup(str);
		*exit_status = 0;
	}
}

void	ft_cd_relative_path(char *str, t_env *pwd, int *exit_status)
{
	char	*ret;
	char	*first_half;
	int		i;

	i = 0;
	first_half = malloc (ft_strlen(pwd->value) + 2);
	while (pwd->value[i])
	{
		first_half[i] = pwd->value[i];
		i++;
	}
	first_half[i] = '/';
	first_half[i + 1] = '\0';
	ret = ft_strjoin(first_half, str);
	free(first_half);
	if (chdir(ret) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", str);
		free(ret);
		*exit_status = 1;
		return ;
	}
	free(pwd->value);
	pwd->value = ret;
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
