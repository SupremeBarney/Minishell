/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 10:09:28 by nipichon          #+#    #+#             */
/*   Updated: 2026/08/22 16:36:59 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_rel_child(char *str, char **args, t_exec_info *info)
{
	char	*ret;
	char	*tmp;
	char	*name;

	reset_child_signals();
	tmp = ft_strjoin(info->pwd, "/");
	name = ft_enlever_str(str);
	ret = ft_strjoin(tmp, name);
	free(tmp);
	free(name);
	if (ft_is_dir(ret))
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		exit(126);
	}
	if (execve(ret, args, info->envp) == -1)
		ft_exec_child_error(str);
}

void	ft_exec_relative_path(char *str, char **args, t_exec_info *info)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		ft_exec_rel_child(str, args, info);
	if (pid > 0)
		info->shell->exit_status = wait_child(pid);
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

static int	ft_env_len(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**ft_envp(t_env *first_env)
{
	char	**ret;
	int		i;
	t_env	*parseur;
	char	*tmp;

	ret = malloc(sizeof(char *) * (ft_env_len(first_env) + 1));
	i = 0;
	parseur = first_env;
	while (parseur)
	{
		if (parseur->equal == 1)
		{
			tmp = ft_strjoin(parseur->name, "=");
			ret[i] = ft_strjoin(tmp, parseur->value);
			free (tmp);
			i++;
		}
		parseur = parseur->next;
	}
	ret[i] = NULL;
	return (ret);
}
