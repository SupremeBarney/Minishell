/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:30:27 by nipichon          #+#    #+#             */
/*   Updated: 2026/07/07 09:45:47 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *first_env)
{
	int		i;
	t_env	*parseur;

	if (!first_env)
		return ;
	parseur = first_env;
	while (parseur)
	{
		i = 0;
		while (parseur->name[i])
		{
			write(1, &parseur->name[i], 1);
			i++;
		}
		i = 0;
		write(1, "=", 1);
		while (parseur->value[i])
		{
			write(1, &parseur->value[i], 1);
			i++;
		}
		parseur = parseur->next;
	}
}
