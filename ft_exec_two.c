/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 12:12:56 by nipichon          #+#    #+#             */
/*   Updated: 2026/08/12 15:12:25 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_find_pwd(t_env *env)
{
	if (!env)
		return (NULL);
	while (env)
	{
		if (ft_strncmp(env->name, "PWD", 4) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	wait_status_to_code(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
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
