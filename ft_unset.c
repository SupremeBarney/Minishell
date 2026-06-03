/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:30:31 by nipichon          #+#    #+#             */
/*   Updated: 2026/06/03 13:22:05 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_env *first_env, char *var_to_unset)
{
	t_env	*finder;
	t_env	*prev;

	if (!first_env || !var_to_unset)
		return ;
	if (first_env->name == var_to_unset)
	{
		first_env = first_env->next;
		return ;
	}
	prev = first_env;
	finder = first_env->next;
	while (finder)
	{
		if (finder->name == var_to_unset)
		{
			prev->next = finder->next;
			return ;
		}
		prev = finder;
		finder = finder->next;
	}
}

