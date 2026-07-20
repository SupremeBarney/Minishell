/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:44:40 by nipichon          #+#    #+#             */
/*   Updated: 2026/07/20 16:46:26 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pour tout les fonctions il faudra rajouter un moyen d'avoir tout les variable d'environement

void	ft_cd(char *str, t_env *first_env)
{
	t_env	*pwd;
	t_env	*home;
	t_env	*parseur;

	if (!first_env)
		ft_which_cd(str, NULL, NULL);
	parseur = first_env;
	pwd = NULL;
	home = NULL;
	while (parseur)
	{
		if (ft_strncmp("PWD", parseur->name, 4) == 0)
			pwd = parseur;
		if (ft_strncmp("HOME", parseur->name, 5) == 0)
			home = parseur;
		parseur = parseur->next;
	}
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
			if (str[2] == '\0')
				ft_cd_backtrack(pwd);
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

void	ft_cd_backtrack(t_env *pwd)
{
	int		i;
	int		slash;
	int		s;

	i = 0;
	slash = 0;
	s = 0;
	while (pwd->value[i])
	{
		if (pwd->value[i] == '/')
			slash++;
		i++;
	}
	i = 0;
	while (pwd->value[i])
	{
		if (pwd->value[i] == '/')
			s++;
		if (s > 0 && s == slash)
		{
			while (pwd->value[i])
			{
				pwd->value[i] = '\0';
				i++;
			}
		}
		i++;
	}
	chdir(pwd->value);
}

void	ft_cd_true_path(char *str, t_env *pwd)
{
	printf("%s\n", str); 
	if (chdir(str) == -1)
	{
		printf("cd: %s: No such file or directory\n", str); //faudra que je fasse une fonction pour return la bonne erreur plus tard
	}
	else
	{
		chdir(str);
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
	if (chdir(ret) == -1)
	{
		chdir(pwd->value);
		return ;
	}
	chdir(ret);
	pwd->value = ret;
}

void	ft_cd_with_nothing(t_env *home, t_env *pwd)
{
	if (!home)
		return ;
	chdir(home->value);
	pwd->value = home->value;
}
