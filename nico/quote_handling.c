/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 14:14:14 by nipichon          #+#    #+#             */
/*   Updated: 2026/04/15 15:04:51 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_quotes(t_current_command *command)
{
	int	i;
	int	cur_arg;

	cur_arg = 0;
	while (command->args->val[cur_arg])
	{
		i = 0;
		while (command->args->val[cur_arg][i])
		{
			if (command->args->val[cur_arg][i] == 39)
			{
				i++;
				while (command->args->val[cur_arg][i]
					&& command->args->val[cur_arg][i] != 39)
				{
					if (is_spec_char(command->args->val[cur_arg][i]) == 1)
						special_into_normal(command->args, cur_arg, i);
				}
			}
			i++;
		}
		cur_arg++;
	}
}

void	double_quotes(t_current_command *command)
{
	int	i;
	int	cur_arg;

	cur_arg = 0;
	while (command->args->val[cur_arg])
	{
		i = 0;
		while (command->args->val[cur_arg][i])
		{
			if (command->args->val[cur_arg][i] == 34)
			{
				i++;
				while (command->args->val[cur_arg][i]
					&& command->args->val[cur_arg][i] != 34)
				{
					if (is_spec_char(command->args->val[cur_arg][i]) == 1
				&& command->args->val[cur_arg][i] != '$')
						special_into_normal(command->args, cur_arg, i);
				}
			}
			i++;
		}
		cur_arg++;
	}
}


