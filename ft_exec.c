/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 10:09:28 by nipichon          #+#    #+#             */
/*   Updated: 2026/07/24 17:36:13 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec(char *str, char **args, t_env *first_env)
{
	char	*pwd;
	char	**envp;
	t_env	*parseur;

	if (!first_env)
		return ;
	parseur = first_env;
	pwd = NULL;
	while (parseur)
	{
		if (ft_strncmp("PWD", parseur->name, 4) == 0)
			pwd = ft_strdup(parseur->value);
		parseur = parseur->next;
	}
	envp = ft_envp(first_env);
	ft_which_exec(str, args, envp, pwd);
}

void	ft_which_exec(char *str, char **args, char **envp, char *pwd)
{
	if (!str)
	{
		//error
		return ;
	}
	else if (str[0] == '.')
	{
		ft_exec_relative_path(str, args, envp, pwd);
	}
	else if (str[0] == '/')
	{
		ft_exec_true_path(str, args, envp);
		return ;
	}
}

void	ft_exec_true_path(char *str, char **args, char **envp)
{
	printf("%s\n", str); 
	if (execve(str, args, envp) == -1)
	{
		printf("cd: %s: No such file or directory\n", str); //faudra que je fasse une fonction pour return la bonne erreur plus tard
	}
	else
	{
		execve(str, args, envp);
	}
}

void	ft_exec_relative_path(char *str, char **args,
	char **envp, char *pwd)
{
	char	*ret;
	int		i;

	str = ft_enlever_str(str);
	i = 0;
	while (pwd[i])
		i++;
	pwd[i] = '/';
	pwd[i + 1] = '\0';
	ret = ft_strjoin(pwd, str);
	if (execve(ret, args, envp) == -1)
	{
		printf("ERROR\n");
		return ;
	}
	else
	{
		printf("it works\n");
		execve(ret, args, envp);
	}
}

char	*ft_enlever_str(char *str)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(ft_strlen(str) - 2);
	while (str[i + 2])
	{
		ret[i] = str[i + 2];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	**ft_envp(t_env *first_env)
{
	char	**ret;
	int		i;
	t_env	*parseur;

	ret = malloc(sizeof(char *));
	i = 0;
	parseur = first_env;
	while (parseur)
	{
		ret[i] = ft_strjoin(parseur->name, "=");
		ret[i] = ft_strjoin(ret[i], parseur->value);
		i++;
		parseur = parseur->next;
	}
	i--;
	ret[i][ft_strlen(ret[i])] = '\0';
	return (ret);
}
