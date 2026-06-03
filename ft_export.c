/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:30:06 by nipichon          #+#    #+#             */
/*   Updated: 2026/06/03 13:17:24 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(t_env *first_env, char *name, char *word)
{
	t_env	*finder;

	if (!first_env || !name)
		return ;
	finder = first_env;
	while (finder)
	{
		if (finder->name == name)
		{
			finder->value = word;
			return ;
		}
		finder = finder->next;
	}
	finder->name = name;
	finder->value = word;
}
