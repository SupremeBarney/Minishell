/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_two.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 13:41:29 by alexfran          #+#    #+#             */
/*   Updated: 2026/08/22 16:24:21 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*add_env_var(t_env **env, char *name, char *value)
{
	t_env	*node;
	t_env	*tail;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = ft_strdup(name);
	node->value = NULL;
	if (value)
		node->value = ft_strdup(value);
	node->next = NULL;
	node->equal = (value != NULL);
	if (!*env)
		return (*env = node, node);
	tail = *env;
	while (tail->next)
		tail = tail->next;
	tail->next = node;
	return (node);
}
