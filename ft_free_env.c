/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 13:43:59 by nipichon          #+#    #+#             */
/*   Updated: 2026/06/03 13:50:10 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(t_env *var)
{
	if (var)
	{
		if (var->value)
			free (var->value);
		if (var->name)
			free (var->name);
		free (var);
	}
}
