/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 15:04:46 by nipichon          #+#    #+#             */
/*   Updated: 2026/05/04 13:29:49 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Maybe the folowing function needs updates, I don't have the full list of special chars but this should be it?

int	is_spec_char(char c)
{
	if (c == '$' || c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}


void	special_into_normal(t_args *args, int arg, int i)
{
	args->is_special[arg][i] == 0;
}