/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:30:27 by nipichon          #+#    #+#             */
/*   Updated: 2026/04/13 14:54:56 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char *name, char *value, t_all_env_var *var_dir)
{
	t_environment_variable	*tmp;

	if (!var_dir)
		return ;
	tmp = var_dir->first_env_var;
	while (tmp && tmp->next)
	{
		if (tmp->variable_name == name)
		{
			tmp->variable_value = value;
			return ;
		}
		tmp = tmp->next;
	}
}
