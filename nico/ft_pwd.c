/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nipichon <nipichon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:23:01 by nipichon          #+#    #+#             */
/*   Updated: 2026/04/15 15:26:35 by nipichon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_pathfile *current_file)
{
	int	i;

	i = 0;
	while (current_file->absolute_pathfile[i])
	{
		write(1, &current_file->absolute_pathfile[i], 1);
		i++;
	}
	write(1, '\n', 1);
}
