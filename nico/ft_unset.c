/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:30:31 by nipichon          #+#    #+#             */
/*   Updated: 2026/04/13 13:50:45 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char var_to_unset, t_all_env_var *dir_of_vars)
{
	t_environment_variable	*tmp;
	t_environment_variable	*tmp_2;

	if (!dir_of_vars)
		return ;
	tmp = dir_of_vars->first_env_var;
	if (tmp == var_to_unset)
	{
		dir_of_vars->first_env_var = dir_of_vars->first_env_var->next;
		free (tmp);
		return ;
	}
	while (tmp || tmp->next)
	{
		tmp_2 = tmp;
		tmp = tmp->next;
		if (tmp->variable == var_to_unset)
		{
			tmp_2->next = tmp->next;
			free (tmp);
			return ;
		}
	}
	return (ft_nothing_to_unset());
}

void	ft_nothing_to_unset(void)
{
	write(1, "Error\n", 6);
	write(1, "Environment variable does not exist\n", 37);
}
