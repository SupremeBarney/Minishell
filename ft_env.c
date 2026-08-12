/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexfran <alexfran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:30:27 by nipichon          #+#    #+#             */
/*   Updated: 2026/07/17 12:41:09 by alexfran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *first_env)
{
	t_env	*parseur;

	if (!first_env)
		return ;
	parseur = first_env;
	while (parseur)
	{
		if (parseur->equal == 1 && parseur->value)
		{
			ft_putstr_fd(parseur->name, 1);
			ft_putstr_fd("=", 1);
			ft_putstr_fd(parseur->value, 1);
			ft_putstr_fd("\n", 1);
		}
		parseur = parseur->next;
	}
}
