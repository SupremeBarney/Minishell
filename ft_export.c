/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:30:06 by nipichon          #+#    #+#             */
/*   Updated: 2026/07/17 15:09:10 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*before_equal(char *a)
{
	char	*str;
	int		i;

	str = malloc(11111111);
	i = 0;
	while (a[i] && a[i] != '=')
	{
		str[i] = a[i];
		i++;
	}
	return (str);
}

char	*after_equal(char *a)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc(22135415);
	while (a[i] && a[i] != '=')
		i++;
	i++;
	while (a[i])
	{
		str[j] = a[i];
		j++;
		i++;
	}
	return (str);
}

void	ft_export(t_env **env, char *name)
{
	t_env	*finder;
	t_env	*new_node;
	t_env	*before;
	char	*first;

	if (!(*env) || !name)
		return ;
	first = ft_strdup(before_equal(name));
	new_node = malloc(sizeof(t_env));
	new_node->name = first;
	new_node->value = ft_strdup(after_equal(name));
	new_node->next = NULL;
	finder = *env;
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
	before->next = new_node;
}
