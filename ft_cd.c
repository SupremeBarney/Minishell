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

void	ft_cd(char *str, t_env *first_env, char **args)
{
	t_env	*pwd;
	t_env	*home;
	t_env	*old_pwd;
	t_env	*parseur;

	if (!first_env)
	{
		ft_which_cd(str, NULL, NULL);
		return ;
	}
	if (args[1] && args[2])
	{
		printf ("bash: cd: too many arguments\n");
		return ;
	}
	parseur = first_env;
	pwd = NULL;
	home = NULL;
	old_pwd = NULL;
	while (parseur)
	{
		if (ft_strncmp("PWD", parseur->name, 4) == 0)
			pwd = parseur;
		if (ft_strncmp("HOME", parseur->name, 5) == 0)
			home = parseur;
		if (ft_strncmp("OLDPWD", parseur->name, 7) == 0)
			old_pwd = parseur;
		parseur = parseur->next;
	}
	old_pwd->value = ft_strdup(pwd->value);
	ft_which_cd(str, pwd, home);
}

void	ft_which_cd(char *str, t_env *pwd, t_env *home)
{
	if (!str || str[0] == '\n')
	{
		ft_cd_with_nothing(home, pwd);
		return ;
	}
	else if (str[0] == '.')
	{
		if (str[1] == '.')
		{
			if (str[2] == '\0' || str[2] =='/')
				ft_cd_backtrack(str, pwd, home);
		}
		if (str[1] == '\0')
		{
			ft_cd_curdir(pwd);
			return ;
		}
	}
	else if (str[0] == '/')
	{
		ft_cd_true_path(str, pwd);
		return ;
	}
	else
	{
		ft_cd_relative_path(str, pwd);
	}
}

void	ft_cd_curdir(t_env *pwd)
{
	if (!pwd)
	{
		printf("cd: error retrieving current directory: ");
		printf("getcwd: cannot access parent directories: ");
		printf("No such file or directory\n");
		return ;
	}
	chdir(pwd->value);
}

void	ft_cd_backtrack(char *str, t_env *pwd, t_env *home)
{
	char	*new_pwd;
	char	*rep;
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
		return ;
	}
	free(pwd->value);
	pwd->value = new_pwd;
	i = 3;
	if (str[2] && str[2] == '/')
	{
		rep = malloc(ft_strlen(str) - 2);
		while (str[i])
		{
			rep[i - 3] = str[i];
			i++;
		}
		rep[i - 3] = '\0';
		str = ft_strdup(rep);
		free(rep);
		ft_which_cd(str, pwd, home);
	}
}

void	ft_cd_true_path(char *str, t_env *pwd)
{
	if (chdir(str) == -1)
	{
		printf("cd: %s: No such file or directory\n", str); //faudra que je fasse une fonction pour return la bonne erreur plus tard
	}
	else
	{
		free(pwd->value);
		pwd->value = ft_strdup(str);
	}
}

void	ft_cd_relative_path(char *str, t_env *pwd)
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
		return ;
	}
	free(pwd->value);
	pwd->value = ret;
}

void	ft_cd_with_nothing(t_env *home, t_env *pwd)
{
	if (!home || !home->value || !home->value[0])
	{
		ft_putstr_fd("bash: cd: HOME not set\n", 2);
		return ;
	}
	chdir(home->value);
	free(pwd->value);
	pwd->value = ft_strdup(home->value);
}
