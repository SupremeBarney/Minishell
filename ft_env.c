/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:30:27 by nipichon          #+#    #+#             */
/*   Updated: 2026/08/12 15:06:12 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env_two(int i, t_env *parseur)
{
	while (parseur)
	{
		if (parseur->equal == 1)
		{
			i = 0;
			while (parseur->name[i])
			{
				write(1, &parseur->name[i], 1);
				i++;
			}
			write(1, "=", 1);
			i = 0;
			while (parseur->value[i])
			{
				write(1, &parseur->value[i], 1);
				i++;
			}
			write(1, "\n", 1);
		}
		parseur = parseur->next;
	}
}

void	ft_env(t_env *first_env)
{
	int		i;
	t_env	*parseur;

	if (!first_env)
		return ;
	parseur = first_env;
	i = 0;
	ft_env_two(i, parseur);
}
