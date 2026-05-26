/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 12:44:40 by nipichon          #+#    #+#             */
/*   Updated: 2026/05/26 12:07:16 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pour tout les fonctions il faudra rajouter un moyen d'avoir tout les variable d'environement

void	ft_which_cd(char *str)
{
	if (!str || str[0] == '\n')
	{
		ft_cd_with_nothing();
		return ;
	}
	else if (str[0] == '.')
	{
		if (str[1] == '.')
		{
			ft_cd_backtrack();
		}
		if (str[1] == '\0')
		{
			ft_cd_curdir();
			return ;
		}
	}
	else if (str[0] == '/')
	{
		ft_cd_true_path(str);
		return ;
	}
	ft_cd_relative_path(str);
}

void	ft_cd_curdir(void)
{
	if (!$PWD)
	{
		printf("cd: error retrieving current directory: ");
		printf("getcwd: cannot access parent directories: ");
		printf("No such file or directory\n");
		return ;
	}
	chdir($PWD);
}


void	ft_cd_backtrack()
{
	char	*str;
	int		i;

	str = malloc (ft_strlen($PWD) + 1);
	if (!str)
	{
		memory_alloc_error();
		return ;
	}
	i = ft_strlen(str) - 1;
	while (str[i] != '/' && i != 0)
		i--;
	if (str[i] == '/')
	{
		str[i] == '\0';
	}
	chdir(str);
}

void	ft_cd_true_path(char *str)
{
	if(chdir(str) == -1)
	{
		printf("cd: %s: No such file or directory\n", str); //faudra que je fasse une fonction pour return la bonne erreur plus tard
	}
	else
	{
		chdir(str);
	}
}

void	ft_cd_relative_path(char *str)
{
	int		i;

	i = 0;
	while (i < nbr_de_fichiers) //il nous faut une variable d'env cacher qui puisse compter le nombre de fichier dans un dir, et de mettre ce nombre a la limit pour pouvoir checker les fichiers un a un
	{
		if(ft_strncmp(str, /*list de fichier dans le current directory[i] */,
			ft_strlen(str)) == 0)
			{
				chdir(str);
				return ;
			}
		i++;
	}
	printf("cd: %s: No such file or directory\n", str);
}

void	ft_cd_with_nothing()
{
	if (!$HOME)
		return ; //si $HOME n'existe pas/nas pas de valeur, sa stop et ne retourne rien
	chdir($HOME) //variable d'environemnent home est le meme chemin que "cd" sans aucun argument, il faut le rajouter sur le parsing au tout depart comme $PWD
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n -1 && s1[i] != '\0' && s2[i] != '\0')
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
