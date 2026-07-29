/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 10:09:28 by nipichon          #+#    #+#             */
/*   Updated: 2026/07/29 17:28:34 by nipichon         ###   ########.fr       */
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
	else if (ft_strncmp(str, "./", 2) == 0)
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
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		if (execve(str, args, envp) == -1)
			printf("cd: %s: No such file or directory\n", str); //faudra que je fasse une fonction pour return la bonne erreur plus tard
		exit(EXIT_FAILURE);
	}
	if (pid > 0)
	{
		waitpid(pid, NULL, 0);
	}
	if (pid < 0)
		perror("Eror");
}

void	ft_exec_relative_path(char *str, char **args,
	char **envp, char *pwd)
{
	char	*ret;
	char	*tmp;
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		tmp = ft_strjoin(pwd, "/");
		str = ft_enlever_str(str);
		ret = ft_strjoin(tmp, str);
		free (tmp);
		if (execve(ret, args, envp) == -1)
		{
			exit(EXIT_FAILURE);
		}
	}
	if (pid > 0)
		waitpid(pid, NULL, 0);
	if (pid < 0)
		perror("EROROR");
}

char	*ft_enlever_str(char *str)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(ft_strlen(str) - 1);
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
	char	*tmp;

	i = 0;
	parseur = first_env;
	while (parseur)
	{
		i++;
		parseur = parseur->next;
	}
	ret = malloc(sizeof(char *) * i);
	i = 0;
	parseur = first_env;
	while (parseur)
	{
		tmp = ft_strjoin(parseur->name, "=");
		ret[i] = ft_strjoin(tmp, parseur->value);
		free (tmp);
		i++;
		parseur = parseur->next;
	}
	ret[i] = NULL;
	i--;
	return (ret);
}
