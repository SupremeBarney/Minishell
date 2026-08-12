/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:30:06 by nipichon          #+#    #+#             */
/*   Updated: 2026/08/12 15:25:51 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*before_equal(char *a)
{
	int		i;
	char	*ret;

	i = 0;
	while (a[i] && a[i] != '=')
		i++;
	ret = malloc(sizeof (char) * i + 1);
	i = 0;
	while (a[i] && a[i] != '=')
	{
		ret[i] = a[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*after_equal(char *a)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (a[i] && a[i] != '=')
		i++;
	if (a[i] != '=')
		return (ft_strdup(""));
	i++;
	while (a[i + j])
		j++;
	ret = malloc(sizeof (char) * j + 1);
	j = 0;
	while (a[i])
	{
		ret[j] = a[i];
		j++;
		i++;
	}
	ret[j] = '\0';
	return (ret);
}

static void	ft_export_insert(t_env **env, t_env *new_node, char *first)
{
	t_env	*finder;
	t_env	*before;

	finder = *env;
	before = NULL;
	while (finder)
	{
		if (ft_strncmp(finder->name, first, ft_strlen(first) + 1) == 0)
		{
			finder->value = new_node->value;
			return ;
		}
		before = finder;
		finder = finder->next;
	}
	if (before)
		before->next = new_node;
	else
		*env = new_node;
}

static void	ft_export_add(t_env **env, char *arg)
{
	t_env	*new_node;
	char	*first;

	first = before_equal(arg);
	new_node = malloc(sizeof(t_env));
	new_node->equal = ft_is_there_an_equal_or_not(arg);
	new_node->name = first;
	new_node->value = after_equal(arg);
	new_node->next = NULL;
	ft_export_insert(env, new_node, first);
}

void	ft_export(t_env **env, char **name, int *exit_status)
{
	int	i;

	i = 1;
	*exit_status = 0;
	if (!name[1])
	{
		if (*env)
			ft_env(*env);
		return ;
	}
	while (name[i])
	{
		if (ft_is_valid_identifier(name[i]) == 1)
			ft_export_add(env, name[i]);
		else
			*exit_status = 1;
		i++;
	}
}
