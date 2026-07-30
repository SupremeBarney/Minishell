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

void	ft_exec(char *str, char **args, t_shell *shell)
{
	t_exec_info	info;
	t_env		*parseur;

	if (!shell->env)
		return ;
	parseur = shell->env;
	info.pwd = NULL;
	while (parseur)
	{
		if (ft_strncmp("PWD", parseur->name, 4) == 0)
			info.pwd = ft_strdup(parseur->value);
		parseur = parseur->next;
	}
	info.envp = ft_envp(shell->env);
	info.shell = shell;
	ft_which_exec(str, args, &info);
}

void	ft_which_exec(char *str, char **args, t_exec_info *info)
{
	if (!str)
	{
		//error
		return ;
	}
	else if (ft_strncmp(str, "./", 2) == 0)
	{
		ft_exec_relative_path(str, args, info);
	}
	else if (str[0] == '/')
	{
		ft_exec_true_path(str, args, info);
		return ;
	}
}

void	ft_exec_true_path(char *str, char **args, t_exec_info *info)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (execve(str, args, info->envp) == -1)
			printf("cd: %s: No such file or directory\n", str); //faudra que je fasse une fonction pour return la bonne erreur plus tard
		exit(EXIT_FAILURE);
	}
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		info->shell->exit_status = wait_status_to_code(status);
	}
	if (pid < 0)
		perror("Eror");
}

void	ft_exec_relative_path(char *str, char **args, t_exec_info *info)
{
	char	*ret;
	char	*tmp;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		tmp = ft_strjoin(info->pwd, "/");
		str = ft_enlever_str(str);
		ret = ft_strjoin(tmp, str);
		free (tmp);
		if (execve(ret, args, info->envp) == -1)
		{
			exit(EXIT_FAILURE);
		}
	}
	if (pid > 0)
	{
		waitpid(pid, &status, 0);
		info->shell->exit_status = wait_status_to_code(status);
	}
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
