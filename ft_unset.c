/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:30:31 by nipichon          #+#    #+#             */
/*   Updated: 2026/07/17 15:29:30 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_env **first_env, char *var_to_unset)
{
	t_env	*tmp;

	if (!first_env || !var_to_unset)
		return ;
	if (ft_strncmp((*first_env)->name, var_to_unset,
			ft_strlen(var_to_unset) + 1) == 0)
	{
		tmp = *first_env;
		*first_env = (*first_env)->next;
		ft_free_env(tmp);
		return ;
	}
	ft_unset_two(first_env, var_to_unset);
}

void	ft_unset_two(t_env **first_env, char *var_to_unset)
{
	t_env	*finder;
	t_env	*prev;

	prev = *first_env;
	finder = (*first_env)->next;
	while (finder)
	{
		if (ft_strncmp(finder->name, var_to_unset,
				ft_strlen(var_to_unset) + 1) == 0)
		{
			if (finder->next)
				prev->next = finder->next;
			else
				prev->next = NULL;
			ft_free_env(finder);
			return ;
		}
		prev = finder;
		finder = finder->next;
	}
}
